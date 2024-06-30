cmake_minimum_required(VERSION 3.10)
project(MarktplatzProjekt)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify directories for source files and headers
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Collect all header and source files using globbing
file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

# Add executable target
add_executable(marktplatz_main ${SOURCE_FILES} ${HEADER_FILES})

# Optionally link libraries (if needed)
# find_package(Boost REQUIRED)
# target_link_libraries(marktplatz_main PRIVATE Boost::boost)

# Optionally set compiler flags
# target_compile_options(marktplatz_main PRIVATE -Wall -Wextra -pedantic)

# Include directories for header files
target_include_directories(marktplatz_main PRIVATE ${INCLUDE_DIR})

