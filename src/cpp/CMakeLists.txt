cmake_minimum_required(VERSION 3.10)
project(ky)

set(CMAKE_CXX_STANDARD 17)

# Recursively find all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include headers if needed
#include_directories(include)
