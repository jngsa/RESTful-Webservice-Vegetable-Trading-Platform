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
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Collect all header and source files using globbing
file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

# Add executable target from example/demo.cpp
add_executable(marktplatz_main ${EXAMPLES_DIR}/demo.cpp ${SOURCE_FILES} ${HEADER_FILES})

# Include directories for header files
target_include_directories(marktplatz_main PRIVATE ${INCLUDE_DIR})

#----------------------------------------------#
#----------Download and Use GoogleTest---------#
#----------------------------------------------#

# Use CMake's FetchContent module to download GoogleTest
include(FetchContent)

# Download GoogleTest (version 1.12.1)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Prevent overriding parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include GoogleTest's CMake configuration
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Enable GoogleTest
enable_testing()

# Collect all test source files using globbing
file(GLOB_RECURSE TEST_FILES ${TESTS_DIR}/*.cpp)

# Add executable target for tests
add_executable(marktplatz_tests ${TEST_FILES} ${SOURCE_FILES})

# Link the GoogleTest libraries and include directories
target_link_libraries(marktplatz_tests gtest gtest_main)
target_include_directories(marktplatz_tests PRIVATE ${INCLUDE_DIR})

# Register the test executable with CTest
add_test(NAME MarktplatzTest COMMAND marktplatz_tests)

