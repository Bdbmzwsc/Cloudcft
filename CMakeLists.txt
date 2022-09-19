cmake_minimum_required(VERSION 3.24.1)
project(Cloudcft)
set(CMAKE_CXX_FLAGS "-std=c++14")
aux_source_directory(./src SRC_DIR)
include_directories(./include)

add_executable(cloudcft ${SRC_DIR})