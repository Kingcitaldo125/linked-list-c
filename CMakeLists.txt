cmake_minimum_required(VERSION 3.10)

project(linked_lists VERSION 1.2.1 LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(STATIC_LIB_NAME ${PROJECT_NAME})
set(SHARED_LIB_NAME ${PROJECT_NAME}_shared)

option(LINK_STATIC "Specify whether or not to use the static vs. shared lib in  linking" ON)

add_executable(main src/main.c)
add_executable(mud src/mud.c)

# Linkage information

if (LINK_STATIC)
  message("Linking static")

  add_library(${STATIC_LIB_NAME} STATIC ${CMAKE_SOURCE_DIR}/src/ll.c)
else()
  message("Linking shared")

  add_library(${SHARED_LIB_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/ll.c)
endif()

# Install information
# Includes
include(GNUInstallDirs)

if (LINK_STATIC)
  target_include_directories(${STATIC_LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
else()
  target_include_directories(${SHARED_LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
endif()

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include/)
target_include_directories(mud PRIVATE ${CMAKE_SOURCE_DIR}/include/)

# Libs
if (LINK_STATIC)
  target_link_libraries(main PRIVATE ${STATIC_LIB_NAME})
  target_link_libraries(mud PRIVATE ${STATIC_LIB_NAME})
else()
  target_link_libraries(main PRIVATE ${SHARED_LIB_NAME})
  target_link_libraries(mud PRIVATE ${SHARED_LIB_NAME})
endif()

