# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MarktplatzProjekt)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify directories for source files and headers
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

# Collect all header and source files using globbing
file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

# Add executable target from example/demo.cpp
add_executable(marktplatz_main ${EXAMPLES_DIR}/demo.cpp ${SOURCE_FILES} ${HEADER_FILES})

# Include directories for header files
target_include_directories(marktplatz_main PRIVATE ${INCLUDE_DIR})

