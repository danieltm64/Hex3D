if (TARGET hex3d-base)
    return()
endif(TARGET hex3d-base)

cmake_minimum_required(VERSION 3.8)
project(hex3d-base)

# LIBRARIES

# Create library target and specify headers and sources.
add_library(hex3d-base SHARED
    include/hex3d/application.hpp
    include/hex3d/config.hpp
    include/hex3d/globals.hpp
    include/hex3d/module.hpp
    src/hex3d/base/application.cpp
)

# Specify include directories.
target_include_directories(hex3d-base PUBLIC include src)

# Make sure we're using standard C++14.
set_target_properties(hex3d-base PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# DEPENDENCIES

cmake_policy(SET CMP0074 OLD)

# Boost.
find_package(Boost)
target_include_directories(hex3d-base PUBLIC ${Boost_INCLUDE_DIRS})

# CML.
target_include_directories(hex3d-base PUBLIC ../third_party/cml/include)

# Hex3D Core.
target_include_directories(hex3d-base PUBLIC ../hex3d-core_module/include)

# dl.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(hex3d-base PUBLIC dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# AGGREGATE BINARIES

add_custom_command(TARGET hex3d-base POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../hex3d-bindir
)
