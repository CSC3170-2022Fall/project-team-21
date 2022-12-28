cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project name
project(simple_db LANGUAGES CXX)

# Create a sources variable with a link to all cpp files to compile
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(./simple_db)
# The unit test module is for our own testing purposes, many of which are still under development
# add_subdirectory(./testing/unit_test)
