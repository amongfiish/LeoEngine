cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rapidxml)

add_library(rapidxml INTERFACE)

target_include_directories(rapidxml INTERFACE include)

