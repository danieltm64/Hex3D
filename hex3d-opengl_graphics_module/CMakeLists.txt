if (TARGET hex3d-opengl_graphics_module)
    return()
endif(TARGET hex3d-opengl_graphics_module)

cmake_minimum_required(VERSION 3.8)
project(hex3d-opengl_graphics_module)

# LIBRARIES

# Create library target and specify headers and sources.
add_library(hex3d-opengl_graphics_module SHARED
    include/hex3d/opengl_graphics_module/config.hpp
    include/hex3d/opengl_graphics_module/opengl_graphics_module.hpp
    src/hex3d/opengl_graphics_module/cube_comp.cpp
    src/hex3d/opengl_graphics_module/opengl_graphics_module.cpp
    ../third_party/glew/src/glew.c
)

# Specify include directories.
target_include_directories(hex3d-opengl_graphics_module PUBLIC include src)

# Make sure we're using standard C++14.
set_target_properties(hex3d-opengl_graphics_module PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# DEPENDENCIES

cmake_policy(SET CMP0074 OLD)

# Boost.
find_package(Boost)
target_include_directories(hex3d-opengl_graphics_module PUBLIC ${Boost_INCLUDE_DIRS})

# GLEW.
target_include_directories(hex3d-opengl_graphics_module PUBLIC ../third_party/glew/include)

# Hex3D Base.
add_subdirectory(../hex3d-base hex3d-base-build)
target_link_libraries(hex3d-opengl_graphics_module PUBLIC hex3d-base)

# Hex3D Core.
add_subdirectory(../hex3d-core_module hex3d-core_module-build)
target_link_libraries(hex3d-opengl_graphics_module PUBLIC hex3d-core_module)

# Hex3D GUI.
add_subdirectory(../hex3d-gui_module hex3d-gui_module-build)
target_link_libraries(hex3d-opengl_graphics_module PUBLIC hex3d-gui_module)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Hex3D X11 GUI.
    add_subdirectory(../hex3d-x11_gui_module hex3d-x11_gui_module-build)
    target_link_libraries(hex3d-opengl_graphics_module PUBLIC hex3d-x11_gui_module)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Hex3D Graphics.
add_subdirectory(../hex3d-graphics_module hex3d-graphics_module-build)
target_link_libraries(hex3d-opengl_graphics_module PUBLIC hex3d-graphics_module)

# OpenGL.
target_link_libraries(hex3d-opengl_graphics_module PUBLIC GL)

# DATA

# Make sure the data files get copied when the library is built.
add_custom_command(TARGET hex3d-opengl_graphics_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)

# AGGREGATE BINARIES

add_custom_command(TARGET hex3d-opengl_graphics_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../hex3d-bindir
)

add_custom_command(TARGET hex3d-opengl_graphics_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/../hex3d-bindir/data
)
