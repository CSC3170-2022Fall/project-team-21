cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project name
project(simple_db LANGUAGES CXX)

# Create a sources variable with a link to all cpp files to compile
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(./simple_db)
add_subdirectory(./testing/unit_test)
