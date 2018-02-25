import bpy
from export_zimesh_operator import ez

def exporterMenu(self, context):
    self.layout.operator_context = 'INVOKE_DEFAULT'
    self.layout.operator(ez.ExportZimesh.bl_idname, text="Zimesh JSON (.json)")
    return None


def register():
    bpy.utils.register_class(ez.ExportZimesh)
    bpy.types.INFO_MT_file_export.append(exporterMenu)
    return None


def unregister():
    bpy.utils.unregister_class(ez.ExportZimesh)
    bpy.types.INFO_MT_file_export.remove(exporterMenu)
    return None
