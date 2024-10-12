cmake_minimum_required(VERSION 3.29)
project(glfw_cpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" GLFW_STANDALONE)

#Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_CPP_BUILD_EXAMPLES "Build the GLFW example programs" ${GLFW_STANDALONE})
option(GLFW_CPP_BUILD_TESTS "Build the GLFW test programs" ${GLFW_STANDALONE})
option(GLFW_CPP_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_CPP_INSTALL "Generate installation target" ON)

add_library(glfw_cpp )
