cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(PROJECT_NAME "LeoEngine")

project(${PROJECT_NAME})

add_subdirectory(lib/boost)
add_subdirectory(lib/sdl)
add_subdirectory(lib/sdl_image)
add_subdirectory(lib/sdl_mixer)
add_subdirectory(lib/sdl_ttf)
add_subdirectory(lib/spdlog)

file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

include_directories(include)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 SDL2_image SDL2_mixer SDL2_ttf spdlog)

include_directories(lib/sdl/include lib/sdl_image/include lib/sdl_mixer/include lib/sdl_ttf lib/spdlog/include lib/boost)

if (APPLE)
    set_target_properties(LeoEngineApp PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
endif()

