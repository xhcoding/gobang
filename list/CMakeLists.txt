cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME "list")
project(${PROJECT_NAME})

add_definitions("-std=c11")
add_definitions("-g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


add_executable(testList test.c list.c)
