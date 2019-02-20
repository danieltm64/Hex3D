if (TARGET hex3d-direct3d11_graphics_module)
    return()
endif(TARGET hex3d-direct3d11_graphics_module)

cmake_minimum_required(VERSION 3.8)
project(hex3d-direct3d11_graphics_module)

# LIBRARIES

# Create library target and specify headers and sources.
add_library(hex3d-direct3d11_graphics_module SHARED
    include/hex3d/direct3d11_graphics_module/config.hpp
    include/hex3d/direct3d11_graphics_module/direct3d11_graphics_module.hpp
    src/hex3d/direct3d11_graphics_module/cube_comp.cpp
    src/hex3d/direct3d11_graphics_module/direct3d11_graphics_module.cpp
)

# Specify include directories.
target_include_directories(hex3d-direct3d11_graphics_module PUBLIC include src)

# Make sure we're using standard C++14.
set_target_properties(hex3d-direct3d11_graphics_module PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# DEPENDENCIES

cmake_policy(SET CMP0074 OLD)

# Hex3D Base.
add_subdirectory(../hex3d-base hex3d-base-build)
target_link_libraries(hex3d-direct3d11_graphics_module PUBLIC hex3d-base)

# Hex3D Core.
add_subdirectory(../hex3d-core_module hex3d-core_module-build)
target_link_libraries(hex3d-direct3d11_graphics_module PUBLIC hex3d-core_module)

# Hex3D Win32 GUI.
add_subdirectory(../hex3d-win32_gui_module hex3d-win32_gui_module-build)
target_link_libraries(hex3d-direct3d11_graphics_module PUBLIC hex3d-win32_gui_module)

# Hex3D Graphics.
add_subdirectory(../hex3d-graphics_module hex3d-graphics_module-build)
target_link_libraries(hex3d-direct3d11_graphics_module PUBLIC hex3d-graphics_module)

# DirectX 11.
target_link_libraries(hex3d-direct3d11_graphics_module PUBLIC d3d11 d3dcompiler)

# DATA

# Make sure the data files get copied when the library is built.
add_custom_command(TARGET hex3d-direct3d11_graphics_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)

# AGGREGATE BINARIES

add_custom_command(TARGET hex3d-direct3d11_graphics_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../hex3d-bindir
)

add_custom_command(TARGET hex3d-direct3d11_graphics_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/../hex3d-bindir/data
)
