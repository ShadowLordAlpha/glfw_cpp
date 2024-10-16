cmake_minimum_required(VERSION 3.29)
project(GLFW_CPP VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

function(add_subdirectory_checked dir)
    if (NOT EXISTS ${dir}/CMakeLists.txt)
        message(FATAL_ERROR
                "Error: Subdirectory " ${dir} " not found\n"
                "You may have cloned the repository without the --recursive flag\n"
                "Use `git submodule update --init --recursive` to get the required dependencies"
        )
    endif ()
    add_subdirectory(${dir})
endfunction()

string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" GLFW_CPP_STANDALONE)

#Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_CPP_BUILD_SHARED_LIBS "Build shared libraries override for GLFW_CPP" OFF)

option(GLFW_CPP_BUILD_EXAMPLES "Build the GLFW example programs" ${GLFW_CPP_STANDALONE})
option(GLFW_CPP_BUILD_TESTS "Build the GLFW test programs" ${GLFW_CPP_STANDALONE})
option(GLFW_CPP_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_CPP_INSTALL "Generate installation target" ON)

add_library(glfw_cpp)
target_include_directories(glfw_cpp PUBLIC include)
target_compile_features(glfw_cpp PUBLIC cxx_std_20)

# Module files
target_sources(glfw_cpp
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        include/glfw.ixx
        include/library.ixx
        include/window.ixx
        include/monitor.ixx
        include/joystick.ixx
        include/cursor.ixx
        include/type.ixx
)

# Source files
target_sources(glfw_cpp
        PRIVATE
        src/library.cpp
        src/monitor.cpp
        src/joystick.cpp
        src/window.cpp
        src/cursor.cpp
)

if (GLFW_CPP_BUILD_EXAMPLES)
    add_subdirectory(external/glad) # We need GLAD for the examples, not for the main library though.
    add_subdirectory(examples) # Actual examples directory
endif ()

# If we are using Emscripten we don't need GLFW as it is provided
if (EMSCRIPTEN)
    target_include_directories(glfw_cpp INTERFACE "${EMSCRIPTEN_ROOT_PATH}/system/include")
    set(CMAKE_CXX_LINKER_WRAPPER_FLAG "")
    target_link_options(glfw_cpp PUBLIC "LINKER:-sUSE_GLFW=3")
else ()
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory_checked(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
    target_link_libraries(glfw_cpp PUBLIC glfw)
endif ()


