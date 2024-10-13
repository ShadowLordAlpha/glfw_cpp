project(glad LANGUAGES C)

add_library(glad src/egl.c src/gl.c src/gles1.c src/gles2.c src/glsc2.c src/vulkan.c src/wgl.c)
target_include_directories(glad PUBLIC include)
