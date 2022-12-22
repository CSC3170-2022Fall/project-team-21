cmake_minimum_required(VERSION 3.16)

include_directories(${PROJECT_SOURCE_DIR}/simple_db)
message(${PROJECT_SOURCE_DIR})
set(APP_SRC test.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${APP_SRC})