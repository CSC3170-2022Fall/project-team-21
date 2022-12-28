cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3")

message(STATUS "The cmake_cxx_flags is: ${CMAKE_CXX_FLAGS}")

# Create a sources variable with a link to all cpp files to compile
FILE(GLOB SOURCES src/*.cpp)

# Add an executable with the above sources
add_executable(simple_db ${SOURCES})

# Set the directories that should be included in the build command for this target
target_include_directories(simple_db
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/simple_db/include
)
