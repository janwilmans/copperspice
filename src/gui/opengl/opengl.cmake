list(APPEND GUI_PUBLIC_INCLUDES
   QOpenGL
   QOpenGL_Buffer
   QOpenGL_DebugMessage
   QOpenGL_ExtraFunctions
   QOpenGL_FramebufferObject
   QOpenGL_PaintDevice
   QOpenGL_Shader
   QOpenGL_ShaderProgram
   QOpenGL_Texture
   QOpenGL_VertexArrayObject
   QOpenGL_VersionFunctions
   QOpenGLFunctions
   QOpenGLFunctions_1_0
   QOpenGLFunctions_2_0
   QOpenGLFunctions_3_0
   QOpenGLFunctions_3_2_Core
   QOpenGLFunctions_3_3_Core
   QOpenGLFunctions_4_0_Core
   QOpenGLFunctions_4_1_Core
   QOpenGLFunctions_4_2_Core
   QOpenGLFunctions_4_3_Core
   QOpenGLFunctions_4_4_Core
   QOpenGLFunctions_4_5_Core
)

list(APPEND GUI_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_es2ext.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_buffer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_debug.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_debugmessage.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_ext.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_extrafunctions.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_framebufferobject.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_paintdevice.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_pixeltransferoptions.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_shader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_shaderprogram.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texture.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_versionfunctions.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_vertexarrayobject.h

   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_0.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_1.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_2.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_3.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_4.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_5.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_2_0.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_2_1.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_0.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_1.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_2_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_2_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_3_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_3_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_0_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_0_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_1_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_1_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_2_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_2_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_3_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_3_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_4_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_4_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_5_compatibility.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_5_core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_es2.h
)

list(APPEND GUI_PRIVATE_INCLUDES
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_framebufferobject_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_paintdevice_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_extensions_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_gradientcache_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texturecache_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_engineshadermanager_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_2pexvertexarray_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_paintengine_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_engineshadersource_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_customshaderstage_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_textureglyphcache_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_shadercache_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_textureblitter_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texture_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texturehelper_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_version_functions_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_vertexarrayobject_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qtriangulator_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qtriangulatingstroker_p.h
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qrbtree_p.h
)

target_sources(CsGui
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_buffer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_debug.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_framebufferobject.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_gradientcache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_paintdevice.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_shaderprogram.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texturecache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_engineshadermanager.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_2pexvertexarray.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_paintengine.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_customshaderstage.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_textureglyphcache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_textureblitter.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texture.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_texturehelper.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_pixeltransferoptions.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_versionfunctions.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_version_functions1.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_version_functions2.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopengl_vertexarrayobject.cpp

   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qtriangulatingstroker.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qtriangulator.cpp

   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_0.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_1.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_2.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_3.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_4.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_1_5.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_2_0.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_2_1.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_0.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_1.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_2_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_2_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_3_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_3_3_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_0_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_0_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_1_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_1_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_2_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_2_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_3_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_3_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_4_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_4_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_5_compatibility.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_4_5_core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/opengl/qopenglfunctions_es2.cpp
)

