import bpy
import bpy_extras
import bmesh
import mathutils
import math
import json
import os

bl_info = {
    "name": "Expoter to Zimesh JSON",
    "author": "bajos",
    "description": "Exports scene to Zinot Engine Zimesh JSON format.",
    "category": "Import-Export",
    "location": "File > Export > Zimesh JSON (.json)"
}

rootKeys = {
    "depTexKey": "dependentTextures",
    "matsKey": "materials",
    "meshesKey": "meshes",
    "objectsKey": "objects"
}

objectKeys = {
    "typeKey": "type",
    "dataKey": "data",
    "matWorldKey": "matrixWorld",
    "parentKey": "parent"
}

uvLayersKey = {
    "uvKey": "uv",
    "tanKey": "tan"
}

meshKeys = {
    "facesGroupsKey": "facesGroups",
    "matSlotsKey": "materialSlots",
    "normalsKey": "normals",
    "uvLayersKey": "uvLayers",
    "verticesKey": "vertices"
}

matKeys = {
    "drawableKey": "drawable",
    "shaderPathKey": "shaderPath",
    "shaderPropertiesKey": "shaderProperties",
    "envprobeTypeKey": "envprobeType",
    "renderPassKey": "renderPass",
    "surfaceTypeKey": "surfaceType"
}


class ZimeshJSONWriter:
    def write(self, packedData, filepath):
        try:
            fileStream = open(filepath, 'w')
            json.dump(packedData, fileStream, indent=4, sort_keys=True)
            fileStream.close()
        except IOError:
            return None
        return None


class DataPacker:
    exporter = None
    toOpenGLSpaceMat = mathutils.Matrix.Rotation(math.radians(-90.0), 4, "X")

    def packMaterials(self, packedData, context):
        packedMaterials = packedData[rootKeys["matsKey"]] = {}

        for mat in bpy.data.materials:
            packedMaterial = packedMaterials[mat.name] = {}
            self.packMaterial(packedMaterial, mat)

        return None

    def packMaterial(self, packedMaterial, mat):
        nodes = mat.node_tree.nodes

        propFrame = nodes.get("zimeshShaderProp")
        if propFrame is None:
            return False

        packedMaterial[matKeys["shaderPathKey"]] = propFrame.label

        propNodes = []
        for node in nodes:
            if node.parent == propFrame:
                propNodes.append(node)

        packedShdProps = packedMaterial[matKeys["shaderPropertiesKey"]] = {}
        for propNode in propNodes:
            packedShdProp = packedShdProps[propNode.name] = None
            self.packShaderProp(packedShdProp, propNode)

        packedMaterial[matKeys["drawableKey"]] = True
        matPropFrame = nodes.get("zimeshMaterialProp")

        packedMaterial[matKeys["envprobeTypeKey"]]
        packedMaterial[matKeys["renderPassKey"]]
        packedMaterial[matKeys["surfaceTypeKey"]]



        return None

    def packMeshObject(self, packedData, obj, context):
        # Triangulate and transform to OpenGL Space
        meshTemp = obj.to_mesh(context.scene, True, "PREVIEW")
        bm = bmesh.new()
        bm.from_mesh(meshTemp)
        bm.transform(self.toOpenGLSpaceMat)
        bmesh.ops.triangulate(bm, faces=bm.faces)
        bm.to_mesh(meshTemp)
        bm.free()

        packedObjects = packedData[rootKeys["objectsKey"]]
        packedMeshes = packedData[rootKeys["meshesKey"]]

        packedObject = packedObjects[obj.name] = {}
        packedMesh = packedMeshes[obj.data.name] = {}

        meshTemp.calc_normals_split()

        packedVertices = packedMesh[meshKeys["verticesKey"]] = []
        packedNormals = packedMesh[meshKeys["normalsKey"]] = []
        for loop in meshTemp.loops:
            norm = loop.normal
            vertIdx = loop.vertex_index
            vert = meshTemp.vertices[vertIdx]

            packedVertices.extend([vert.co[0], vert.co[1], vert.co[2]])
            packedNormals.extend([norm[0], norm[1], norm[2]])

        packedUvLayers = packedMesh[meshKeys["uvLayersKey"]] = {}
        for uvLayer in meshTemp.uv_layers:
            uvLayerData = packedUvLayers[uvLayer.name] = {}
            uvComponents = uvLayerData[uvLayersKey["uvKey"]] = []
            tanComponents = uvLayerData[uvLayersKey["tanKey"]] = []

            for uvLoop in uvLayer.data:
                uvComponents.extend([uvLoop.uv[0], uvLoop.uv[1]])

            meshTemp.calc_tangents(uvLayer.name)
            for loop in meshTemp.loops:
                tan = loop.tangent
                bitanSign = loop.bitangent_sign
                tanComponents.extend([tan[0], tan[1], tan[2], bitanSign])

        packedMatSlots = packedMesh[meshKeys["matSlotsKey"]] = []
        for slot in obj.material_slots:
            packedMatSlots.append(slot.material.name)

        packedFaces = packedMesh[meshKeys["facesGroupsKey"]] = {}
        for matSlotIndex in range(0, len(obj.material_slots)):
            packedFaces[matSlotIndex] = []

        for polygon in meshTemp.polygons:
            if polygon.loop_total >= 3:
                fg = packedFaces[polygon.material_index]
                fg.extend([polygon.loop_indices[0], polygon.loop_indices[1], polygon.loop_indices[2]])

        packedObject[objectKeys["typeKey"]] = "mesh"
        packedObject[objectKeys["dataKey"]] = obj.data.name
        if obj.parent is not None:
            packedObject[objectKeys["parentKey"]] = obj.parent.name
        else:
            packedObject[objectKeys["parentKey"]] = None

        matWorld = obj.matrix_world
        packedObject[objectKeys["matWorldKey"]] = [
            matWorld.col[0][0], matWorld.col[0][1], matWorld.col[0][2], matWorld.col[0][3],
            matWorld.col[1][0], matWorld.col[1][1], matWorld.col[1][2], matWorld.col[1][3],
            matWorld.col[2][0], matWorld.col[2][1], matWorld.col[2][2], matWorld.col[2][3],
            matWorld.col[3][0], matWorld.col[3][1], matWorld.col[3][2], matWorld.col[3][3]
        ]

        # Free temporary mesh (with applied modifiers of obj)
        bpy.data.meshes.remove(meshTemp)
        return

    def packLightObject(self, packedData, light, context):
        return

    def packObjects(self, packedData, context):
        objectsToExport = None
        if self.exporter.selectedOnly:
            objectsToExport = context.selected_objects
        else:
            objectsToExport = context.scene.objects

        packedData[rootKeys["objectsKey"]] = {}
        packedData[rootKeys["meshesKey"]] = {}

        for obj in objectsToExport:
            if obj.type == "MESH":
                self.packMeshObject(packedData, obj, context)
            if obj.type == "LIGHT":
                self.packLightObject(packedData, obj, context)
        return None

    def packData(self, exporter, context):
        self.exporter = exporter
        packedData = {}
        self.packMaterials(packedData, context)
        self.packObjects(packedData, context)
        return packedData


class ExportZimesh(bpy.types.Operator, bpy_extras.io_utils.ExportHelper):
    bl_idname = 'export.zimesh'
    bl_label = 'Export Zimesh JSON'

    # ExportHelper mixin class uses this
    filename_ext = ".json"
    filter_glob = bpy.props.StringProperty(default='*.json', options={'HIDDEN'})

    selectedOnly = bpy.props.BoolProperty(
        name="Export selected only",
        description="Export only objects selected on scene",
        default=True
    )

    vsFormat = bpy.props.StringProperty(
        name="Vertex shader path format",
        description="format for vertex shader path. Use {matname} for material name and {filename} for file name.",
        default="/media/shaders/{matname}_vs.glsl"
    )
    fsFormat = bpy.props.StringProperty(
        name="Fragment shader path format",
        description="format for fragment shader path. Use {matname} for material name and {filename} for file name.",
        default="/media/shaders/{matname}_fs.glsl"
    )

    packer = DataPacker()
    writer = ZimeshJSONWriter()

    def execute(self, context):
        packedData = self.packer.packData(self, context)
        self.writer.write(packedData, self.filepath)

        return {'FINISHED'}


def exporterMenu(self, context):
    self.layout.operator_context = 'INVOKE_DEFAULT'
    self.layout.operator(ExportZimesh.bl_idname, text="Zimesh JSON (.json)")
    return None


def register():
    bpy.utils.register_class(ExportZimesh)
    bpy.types.INFO_MT_file_export.append(exporterMenu)
    return None


def unregister():
    bpy.utils.unregister_class(ExportZimesh)
    bpy.types.INFO_MT_file_export.remove(exporterMenu)
    return None
