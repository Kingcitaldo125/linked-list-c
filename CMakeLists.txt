cmake_minimum_required(VERSION 3.10)

project(linked_lists VERSION 1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(linked_lists STATIC src/main.c)
add_library(linked_lists_shared SHARED src/main.c)

add_executable(out src/main.c)

target_include_directories(out PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_include_directories(linked_lists PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_include_directories(linked_lists_shared PUBLIC "${CMAKE_SOURCE_DIR}/include/")
