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

# Include directory for header files
include_directories(${PROJECT_SOURCE_DIR}/include)  # Include 'include' directory

# Collect all header and source files using globbing
file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

#----------------------- PYBIND11 -----------------------#

# Find and use pybind11 (adjust as necessary)
find_package(pybind11 REQUIRED)

# Ensure extra directory is included for pybind.cpp
set(EXTRA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extra)
file(GLOB_RECURSE EXTRA_FILES ${EXTRA_DIR}/*.cpp)

# Build Python module named 'konto'
pybind11_add_module(konto
  ${EXTRA_DIR}/konto_pybind.cpp  
  ${SRC_DIR}/konto.cpp
)

# Build Python module named 'bank'
pybind11_add_module(bank
  ${EXTRA_DIR}/bank_pybind.cpp  
  ${SRC_DIR}/bank.cpp
)

# Build Python module named 'ware'
pybind11_add_module(ware
  ${EXTRA_DIR}/ware_pybind.cpp  
  ${SRC_DIR}/ware.cpp
)

#--------------------------------------------------------#

# Add executable target from example/demo.cpp
add_executable(marktplatz_main ${EXAMPLES_DIR}/demo.cpp ${SOURCE_FILES} ${HEADER_FILES})

# Include directories for header files
target_include_directories(marktplatz_main PRIVATE ${INCLUDE_DIR})

