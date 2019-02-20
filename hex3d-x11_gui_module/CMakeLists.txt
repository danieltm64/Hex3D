if (TARGET hex3d-x11_gui_module)
    return()
endif(TARGET hex3d-x11_gui_module)

cmake_minimum_required(VERSION 3.8)
project(hex3d-x11_gui_module)

# LIBRARIES

# Create library target and specify headers and sources.
add_library(hex3d-x11_gui_module SHARED
    include/hex3d/x11_gui_module/config.hpp
    include/hex3d/x11_gui_module/x11_gui_module.hpp
    src/hex3d/x11_gui_module/x11_gui_module.cpp
    #../third_party/glew/src/glew.c
)

# Specify include directories.
target_include_directories(hex3d-x11_gui_module PUBLIC include src)

# Make sure we're using standard C++14.
set_target_properties(hex3d-x11_gui_module PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# DEPENDENCIES

cmake_policy(SET CMP0074 OLD)

# GLEW.
#target_include_directories(hex3d-x11_gui_module PUBLIC ../third_party/glew/include)

# Hex3D Base.
add_subdirectory(../hex3d-base hex3d-base-build)
target_link_libraries(hex3d-x11_gui_module PUBLIC hex3d-base)

# Hex3D Core.
add_subdirectory(../hex3d-core_module hex3d-core_module-build)
target_link_libraries(hex3d-x11_gui_module PUBLIC hex3d-core_module)

# Hex3D GUI.
add_subdirectory(../hex3d-gui_module hex3d-gui_module-build)
target_link_libraries(hex3d-x11_gui_module PUBLIC hex3d-gui_module)

# X11.
target_link_libraries(hex3d-x11_gui_module PUBLIC X11)

# OpenGL.
target_link_libraries(hex3d-x11_gui_module PUBLIC GL)

# AGGREGATE BINARIES

add_custom_command(TARGET hex3d-x11_gui_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../hex3d-bindir
)
