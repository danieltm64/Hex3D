cmake_minimum_required(VERSION 3.8)
project(hex3d-demo1)

# LIBRARIES

# Create library target and specify headers and sources.
add_executable(hex3d-demo1
    src/hex3d/demo1/main.cpp
)

# Specify include directories.
target_include_directories(hex3d-demo1 PUBLIC include src)

# Make sure we're using standard C++14.
set_target_properties(hex3d-demo1 PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# DEPENDENCIES

cmake_policy(SET CMP0074 OLD)

# Hex3D Base.
add_subdirectory(../hex3d-base hex3d-base-build)
target_link_libraries(hex3d-demo1 PUBLIC hex3d-base)

# Hex3D Core.
add_subdirectory(../hex3d-core_module hex3d-core_module-build)
target_link_libraries(hex3d-demo1 PUBLIC hex3d-core_module)

# DATA

# Make sure the data files get copied when the executable is built.
add_custom_command(TARGET hex3d-demo1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)

# AGGREGATE BINARIES

add_custom_command(TARGET hex3d-demo1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../hex3d-bindir
)

add_custom_command(TARGET hex3d-demo1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/../hex3d-bindir/data
)
