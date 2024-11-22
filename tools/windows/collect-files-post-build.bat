cd ..\..

mkdir Build

rem RETRIEVE GAME BINARY
copy Debug\MinecartMadness.exe Build

rem COPY RESOURCES INTO BUILD DIRECTORY
robocopy textures\ Build\textures\ /e

rem COPY LIBRARY FILES INTO BUILD DIRECTORY
copy lib\sdl\lib\x64\SDL2.dll Build
copy lib\sdl_image\lib\x64\SDL2_image.dll Build
copy lib\sdl_mixer\lib\x64\SDL2_mixer.dll Build
copy lib\sdl_ttf\lib\x64\SDL2_ttf.dll Build

rmdir /S /Q Debug

cd Build

