if (EMSCRIPTEN)

else ()
    add_executable(basic basic.cpp)
    target_link_libraries(basic PRIVATE glad glfw_cpp)

    add_executable(windows windows.cpp)
    target_link_libraries(windows PRIVATE glad glfw_cpp)

    # add_executable(wave wave.cpp)
    # target_link_libraries(wave PRIVATE glad glfw_cpp)
    # include_directories(../external)
endif ()
