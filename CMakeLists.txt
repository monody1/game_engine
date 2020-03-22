cmake_minimum_required(VERSION 3.15)
project(game_engine)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE MATCHES "Debug" )
    add_definitions(-DMY_DEBUG)
endif ()

include_directories(
        ${CMAKE_SOURCE_DIR}/Framework/common
        ${CMAKE_SOURCE_DIR}/Framework/interface
)

add_subdirectory(
        ${CMAKE_SOURCE_DIR}/framework
)

add_subdirectory(
        ${CMAKE_SOURCE_DIR}/empty
)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest-master)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)

#add_subdirectory(
#        ${CMAKE_SOURCE_DIR}/third_party/glfw-master
#)
#
#add_subdirectory(
#        ${CMAKE_SOURCE_DIR}/third_party/glfw-master/examples
#)
