cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(boost)

add_library(boost INTERFACE)

target_include_directories(boost INTERFACE include)
