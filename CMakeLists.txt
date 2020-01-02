cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(HelloWorld LANGUAGES C CXX)

# find_include and find_library

if(NOT DEFINED ENV{GL3W_PATH})
    message("env variable GL3W_PATH is needed.")
endif()
if(NOT DEFINED ENV{GLFW_PATH})
    message("env variable GLFW_PATH is needed.")
endif()

find_path(GL3W_INCLUDE_DIR
    GL/gl3w.h
    HINTS
        $ENV{GL3W_PATH}/include/gl3w
)

find_path(GLFW_INCLUDE_DIR
    GLFW/glfw3.h
    HINTS
        $ENV{GLFW_PATH}/include
)

find_library(GLFW_LIBRARY_DEBUG
    glfw3dll
    HINTS
        $ENV{GLFW_PATH}/lib/Debug
)

find_library(GLFW_LIBRARY_RELEASE
    glfw3dll
    HINTS
        $ENV{GLFW_PATH}/lib/Release
)

# end find_include and find_library

add_library(gl3w
    STATIC
    ${GL3W_INCLUDE_DIR}/GL/gl3w.h
    gl3w.c
)
set_target_properties(gl3w PROPERTIES LINKER_LANGUAGE C)
target_include_directories(gl3w PRIVATE ${GL3W_INCLUDE_DIR})

add_executable(hello main.cpp LoadShaders.cpp)

target_include_directories(hello PRIVATE ${CMAKE_SOURCE_DIR} ${GL3W_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

target_link_libraries(hello
    PRIVATE
    debug ${GLFW_LIBRARY_DEBUG}
    optimized ${GLFW_LIBRARY_RELEASE}
    gl3w)
