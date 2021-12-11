cmake_minimum_required(VERSION 3.10)

project(linked_lists VERSION 1.0)

set(PROJECT_SRC_DIR "${CMAKE_SOURCE_DIR}/../")
set(TEST_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 11)

enable_testing()

find_package(GTest REQUIRED)

find_library(LLISTS linked-list-c
    HINTS ${PROJECT_SRC_DIR}
    PATH_SUFFIXES /bin /build /lib /bin/lib /build/lib)

add_executable(app-test test.cpp)

target_link_libraries(app-test ${LLISTS} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

target_include_directories(app-test PUBLIC ${PROJECT_SRC_DIR}/include)

add_test(NAME app-test-test COMMAND app-test)
