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

    def packDependentTextures(self, packedData, context):
        packedTextures = set()
        for mat in bpy.data.materials:
            for node in mat.node_tree.nodes:
                if type(node) is not bpy.types.ShaderNodeTexImage:
                    continue

                if (node.image.source != "FILE") or (node.image.type != "IMAGE"):
                    continue

                fp = node.image.filepath
                packedTextures.add(os.path.splitext(os.path.normpath(fp))[0] + ".zitex")
        packedData["dependent_textures"] = list(packedTextures)
        return None

    def packMaterials(self, packedData, context):
        packedMaterials = packedData["materials"] = {}

        for mat in bpy.data.materials:
            packedMaterial = packedMaterials[mat.name] = {}
            packedMaterial["metalness"] = mat.get("metalness", 0.1)
            packedMaterial["roughness"] = mat.get("roughness", 0.5)

            packedMaterial["envmap_source"] = "static_object_world_cubemap"
            packedMaterial["surface_type"] = "opaque"
            packedMaterial["drawable"] = True
            packedMaterial["transparency"] = 0.0

            basename = os.path.basename(bpy.data.filepath)
            filename = str(os.path.splitext(basename)[0]).replace(".", "_")

            packedMaterial["vertex_shader"] = self.exporter.vsFormat.format(filename=filename, matname=mat.name)
            packedMaterial["fragment_shader"] = self.exporter.fsFormat.format(filename=filename, matname=mat.name)

            dependentTextures = set()
            for node in mat.node_tree.nodes:
                if type(node) is not bpy.types.ShaderNodeTexImage:
                    continue

                if (node.image.source != "FILE") or (node.image.type != "IMAGE"):
                    continue

                fp = node.image.filepath
                dependentTextures.add(os.path.splitext(os.path.normpath(fp))[0] + ".zitex")
            packedMaterial["dependent_textures"] = list(dependentTextures)
        return None

    def packMeshObject(self, obj, packedData, context):
        # Triangulate and transform to OpenGL Space
        meshTemp = obj.to_mesh(context.scene, True, "PREVIEW")
        bm = bmesh.new()
        bm.from_mesh(meshTemp)
        bm.transform(self.toOpenGLSpaceMat)
        bmesh.ops.triangulate(bm, faces=bm.faces)
        bm.to_mesh(meshTemp)
        bm.free()

        packedObjects = packedData["objects"]
        packedMeshes = packedData["meshes"]

        packedObject = packedObjects[obj.name] = {}
        packedMesh = packedMeshes[obj.data.name] = {}

        packedVertices = packedMesh["vertices"] = []
        packedNormals = packedMesh["normals"] = []
        for vert in meshTemp.vertices:
            packedVertices.extend([vert.co[0], vert.co[1], vert.co[2]])
            packedNormals.extend([vert.normal[0], vert.normal[1], vert.normal[2]])

        packedUvLayers = packedMesh["uv_layers"] = {}
        for uvLayer in meshTemp.uv_layers:
            uvLayerData = packedUvLayers[uvLayer.name] = []
            for uvItem in uvLayer.data:
                uvLayerData.extend([uvItem.uv[0], uvItem.uv[1]])

        packedMatSlots = packedMesh["material_slots"] = []
        for slot in obj.material_slots:
            packedMatSlots.append(slot.material.name)

        packedFaces = packedMesh["faces"] = {}
        for matSlotIndex in range(0, len(obj.material_slots)):
            packedFaces[matSlotIndex] = []

        for polygon in meshTemp.polygons:
            packedFaces[polygon.material_index].extend([polygon.vertices[0],
                                                        polygon.vertices[1],
                                                        polygon.vertices[2]])

        packedObject["type"] = "mesh"
        packedObject["data"] = obj.data.name
        if obj.parent is not None:
            packedObject["parent"] = obj.parent.name
        else:
            packedObject["parent"] = None

        packedObject["matrix"] = [obj.matrix_world[0][0], obj.matrix_world[1][0], obj.matrix_world[2][0],
                                  obj.matrix_world[3][0],
                                  obj.matrix_world[0][1], obj.matrix_world[1][1], obj.matrix_world[2][1],
                                  obj.matrix_world[3][1],
                                  obj.matrix_world[0][2], obj.matrix_world[1][2], obj.matrix_world[2][2],
                                  obj.matrix_world[3][2],
                                  obj.matrix_world[0][3], obj.matrix_world[1][3], obj.matrix_world[2][3],
                                  obj.matrix_world[3][3]]

        # Free temporary mesh (with applied modifiers of obj)
        bpy.data.meshes.remove(meshTemp)
        return

    def packLightObject(self, obj, packedData, context):
        return

    def packObjects(self, packedData, context):
        objectsToExport = None
        if self.exporter.selectedOnly:
            objectsToExport = context.selected_objects
        else:
            objectsToExport = context.scene.objects

        packedData["objects"] = {}
        packedData["meshes"] = {}

        for obj in objectsToExport:
            if obj.type == "MESH":
                self.packMeshObject(obj, packedData, context)
            if obj.type == "LIGHT":
                self.packLightObject(obj, packedData, context)
        return None

    def packData(self, context, exporter):
        self.exporter = exporter
        packedData = {}
        self.packDependentTextures(packedData, context)
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
        packedData = self.packer.packData(context, self)
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
