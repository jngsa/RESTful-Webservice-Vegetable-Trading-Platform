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
set(EXTRA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extra)

# Set output directory for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directory for header files
include_directories(${INCLUDE_DIR})

# Collect all header and source files using globbing
file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

# Find and use pybind11
find_package(pybind11 REQUIRED)

# Collect extra source files for pybind11 modules
file(GLOB_RECURSE EXTRA_FILES ${EXTRA_DIR}/*.cpp)

# Function to add Python module and set its output directory to EXTRA_DIR
function(add_python_module module_name)
    pybind11_add_module(${module_name} ${ARGN})
    set_target_properties(${module_name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${EXTRA_DIR}
    )
endfunction()

# Build Python modules
add_python_module(konto
    ${EXTRA_DIR}/konto_pybind.cpp
    ${SRC_DIR}/konto.cpp
    ${SRC_DIR}/ware.cpp
    ${SRC_DIR}/bank.cpp
)

add_python_module(bank
    ${EXTRA_DIR}/bank_pybind.cpp
    ${SRC_DIR}/bank.cpp
    ${SRC_DIR}/ware.cpp
)

add_python_module(ware
    ${EXTRA_DIR}/ware_pybind.cpp
    ${SRC_DIR}/ware.cpp
)

# Add executable target from example/demo.cpp
add_executable(marktplatz_main ${EXAMPLES_DIR}/demo.cpp ${SOURCE_FILES} ${HEADER_FILES})

# Include directories for header files for executable
target_include_directories(marktplatz_main PRIVATE ${INCLUDE_DIR})

# Link the C++ standard library if necessary (conditionally for GNU/Clang)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(konto PRIVATE stdc++fs)
    target_link_libraries(bank PRIVATE stdc++fs)
    target_link_libraries(ware PRIVATE stdc++fs)
endif()

# Link pybind11 to the main executable (optional based on requirement)
target_link_libraries(marktplatz_main PRIVATE pybind11::module)

#----------------------------------------------#
#----------Download and Use GoogleTest---------#
#----------------------------------------------#
# Use CMake's FetchContent module to download GoogleTest
include(FetchContent)

# Download GoogleTest (version 1.12.1)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
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