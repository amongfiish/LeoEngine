Turbo City's *Leo Engine*.

This engine was originally created for a remake of Minecart Madness (which ultimately led to nothing) but has since been repurposed for a number of in-development projects.

# Dependencies
Leo Engine's build process uses [CMake](https://cmake.org/download/) and as such it is necessary that you have it installed on your system. Every other dependency is included in this repository.

# External Libraries Used
 - [SDL](https://github.com/libsdl-org/SDL)
 - [SDL Image](https://github.com/libsdl-org/SDL_image)
 - [SDL Mixer](https://github.com/libsdl-org/SDL_mixer)
 - [SDL TTF](https://github.com/libsdl-org/SDL_ttf)
 - [spdlog](https://github.com/gabime/spdlog)

# Building from Source
To build the engine from source:

1. Clone this repository (`git clone https://github.com/amongfiish/LeoEngine.git`)
2. Run the pre-first-build script (specific to your operating system) from the tools folder.
3. Configure the build script with CMake (`cmake . -B build`).
4. Build. On Windows, this opening the CMake-generated Visual Studio project; on Unix, you can simply use the generated Makefile.

