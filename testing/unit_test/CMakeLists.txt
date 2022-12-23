cmake_minimum_required(VERSION 3.16)

include_directories(${PROJECT_SOURCE_DIR}/simple_db/include)
set(APP_SRC test.cpp)
add_executable(simple_db_test ${APP_SRC})