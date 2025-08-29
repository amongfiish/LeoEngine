cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sdl_gfx)

file(GLOB SOURCES src/*.c)

find_package(SDL2 REQUIRED)

add_library(sdl_gfx ${SOURCES})

target_link_libraries(sdl_gfx PRIVATE SDL2)
target_include_directories(sdl_gfx PUBLIC include SDL2_INCLUDE_DIR)

