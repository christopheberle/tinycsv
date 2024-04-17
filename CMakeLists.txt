cmake_minimum_required(VERSION 3.28)
project(tinycsv-demo C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(${PROJECT_NAME} demo/demo.c)
add_library(tinycsv SHARED src/tinycsv.c)

target_link_libraries(${PROJECT_NAME} tinycsv)
