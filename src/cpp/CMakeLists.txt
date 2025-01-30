cmake_minimum_required(VERSION 3.10)
project(ky)

set(CMAKE_CXX_STANDARD 17)

# Recursively find all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include headers if needed
#include_directories(include)

# Define the source directory (where your resources directory is)
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/../../resources")

# Define the destination directory (where you want to copy it in the build directory)
set(DEST_DIR "${CMAKE_BINARY_DIR}")

# Copy the entire 'resources' directory from source to build
file(COPY ${SOURCE_DIR} DESTINATION ${DEST_DIR})

