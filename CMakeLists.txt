cmake_minimum_required(VERSION 3.10)

project(linked_lists VERSION 1.2.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(linked_lists STATIC src/ll.c)
add_library(linked_lists_shared SHARED src/ll.c)

add_executable(main src/main.c)
add_executable(mud src/mud.c)

target_link_libraries(main PRIVATE linked_lists)
target_link_libraries(mud PRIVATE linked_lists)

target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_include_directories(mud PUBLIC "${CMAKE_SOURCE_DIR}/include/")

target_include_directories(linked_lists PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_include_directories(linked_lists_shared PUBLIC "${CMAKE_SOURCE_DIR}/include/")
