cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(PROJECT_NAME "LeoEngine")
set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR})

project(${PROJECT_NAME})

if (WIN32)
    add_library(SDL3 SHARED IMPORTED)
    add_library(SDL3_image SHARED IMPORTED)
    add_library(SDL3_mixer SHARED IMPORTED)
    add_library(SDL3_ttf SHARED IMPORTED)
else ()
    set(SDL3MIXER_VENDORED ON)

    add_subdirectory(lib/sdl)
    add_subdirectory(lib/sdl_image)
    add_subdirectory(lib/sdl_mixer)
    add_subdirectory(lib/sdl_ttf)
endif()

add_subdirectory(lib/spdlog)
add_subdirectory(lib/boost)
add_subdirectory(lib/tweeny)

file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL3.lib SDL3_image.lib SDL3_mixer.lib SDL3_ttf.lib spdlog boost)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf spdlog boost)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include lib/sdl/include lib/sdl_image/include lib/sdl_mixer/include lib/sdl_ttf/include lib/spdlog/include ${CMAKE_SOURCE_DIR}/lib/boost/include)
