cmake_minimum_required(VERSION 3.5)

include_directories(${PROJECT_SOURCE_DIR}/simple_db/include)

FILE(GLOB SOURCES *.cpp ${PROJECT_SOURCE_DIR}/simple_db/src/*.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/simple_db/src/main.cpp)

add_executable(simple_db_test ${SOURCES})