cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(PROJECT_NAME "LeoEngine")

project(${PROJECT_NAME})

add_subdirectory(lib/boost)
add_subdirectory(lib/sdl)
add_subdirectory(lib/sdl_image)
add_subdirectory(lib/sdl_mixer)
add_subdirectory(lib/sdl_ttf)
add_subdirectory(lib/spdlog)

file(GLOB SOURCES src/*.cpp src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC lib/boost lib/sdl lib/sdl_image lib/sdl_mixer lib/sdl_ttf lib/spdlog)

if (APPLE)
    set_target_properties(LeoEngineApp PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
endif()

