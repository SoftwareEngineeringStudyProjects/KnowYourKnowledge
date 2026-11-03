cmake_minimum_required(VERSION 3.15)
project(KnowYourKnowledge CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Gather source files or point to main
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the executable 'ky'
add_executable(ky ${SOURCES})
