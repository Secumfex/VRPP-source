cmake_minimum_required(VERSION 2.8)

if(MSVC)

find_package(KINECT REQUIRED)
add_definitions("-DUSE_KINECT")


endif()

include(${CMAKE_MODULE_PATH}/DefaultExecutable.cmake)