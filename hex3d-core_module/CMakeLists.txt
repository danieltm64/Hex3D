if (TARGET hex3d-core_module)
    return()
endif(TARGET hex3d-core_module)

cmake_minimum_required(VERSION 3.8)
project(hex3d-core_module)

# LIBRARIES

# Create library target and specify headers and sources.
add_library(hex3d-core_module SHARED
    include/hex3d/core_module/config.hpp
    include/hex3d/core_module/core_module.hpp
    src/hex3d/core_module/component.cpp
    src/hex3d/core_module/core_module.cpp
    src/hex3d/core_module/entity.cpp
    src/hex3d/core_module/entity_graph.cpp
    src/hex3d/core_module/pass_event.cpp
    src/hex3d/core_module/transform.cpp
    src/hex3d/core_module/transform_comp.cpp
    src/hex3d/core_module/utils.cpp
    src/hex3d/core_module/vector2d.cpp
    src/hex3d/core_module/vector3d.cpp
    src/hex3d/core_module/vector4d.cpp
)

# Specify include directories.
target_include_directories(hex3d-core_module PUBLIC include src)

# Make sure we're using standard C++14.
set_target_properties(hex3d-core_module PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# DEPENDENCIES

cmake_policy(SET CMP0074 OLD)

# Hex3D Base.
add_subdirectory(../hex3d-base hex3d-base-build)
target_link_libraries(hex3d-core_module PUBLIC hex3d-base)

# AGGREGATE BINARIES

add_custom_command(TARGET hex3d-core_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../hex3d-bindir
)
