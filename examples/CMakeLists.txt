
if (EMSCRIPTEN)

else ()
    add_executable(basic basic.cpp)
    target_link_libraries(basic PRIVATE glad glfw_cpp)
endif ()
