cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(LeoEngineApp)

file(GLOB SOURCES src/*.cpp src/*.hpp)

if (WIN32)
    set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

    set(SDL2_INCLUDE_DIRS "${LIB_DIR}/sdl/include")
    set(SDL2_IMAGE_INCLUDE_DIRS "${LIB_DIR}/sdl_image/include")
    set(SDL2TTF_INCLUDE_DIR "${LIB_DIR}/sdl_ttf/include")
    set(SDL2_MIXER_INCLUDE_DIR "${LIB_DIR}/sdl_mixer/include")

    # check if x86 or x86_64
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(WIN_ARCHITECTURE "x64")
    else ()
        set(WIN_ARCHITECTURE "x86")
    endif ()

    set(SDL2_LIBRARIES "${LIB_DIR}/sdl/lib/${WIN_ARCHITECTURE}/SDL2.lib;${LIB_DIR}/sdl/lib/${WIN_ARCHITECTURE}/SDL2main.lib")
    set(SDL2_IMAGE_LIBRARIES "${LIB_DIR}/sdl_image/lib/${WIN_ARCHITECTURE}/SDL2_image.lib")
    set(SDL2TTF_LIBRARY "${LIB_DIR}/sdl_ttf/lib/${WIN_ARCHITECTURE}/SDL2_ttf.lib")
    set(SDL2_MIXER_LIBRARY "${LIB_DIR}/sdl_mixer/lib/${WIN_ARCHITECTURE}/SDL2_mixer.lib")

    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

    set(SPDLOG_INCLUDE_DIR "${LIB_DIR}/spdlog/include")
    set(SPDLOG_LIBRARY "${LIB_DIR}/spdlog/lib/spdlogd.lib")
else ()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2TTF REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(spdlog REQUIRED)
endif ()

if (WIN32)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SPDLOG_INCLUDE_DIR})
else ()
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
endif ()

add_executable(LeoEngineApp ${SOURCES})

if (WIN32)
    target_link_libraries(LeoEngineApp ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SPDLOG_LIBRARY})
else ()
    target_link_libraries(LeoEngineApp ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2_MIXER_LIBRARY} spdlog::spdlog)
endif ()

if (APPLE)
    set_target_properties(LeoEngineApp PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
endif()

