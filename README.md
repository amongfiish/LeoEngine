The Leo Engine. Originally made for a Minecart Madness re-write, now used primarily for Alley Cats, a mobile bowling game.

# Dependencies
Leo Engine's build process uses [CMake](https://cmake.org/download/) and as such it is necessary that you have it installed on your system. Every other dependency is included in this repository.

# Building from Source
To build the engine from source:

1. Pull the source code from this repository by entering `git clone https://github.com/amongfiish/LeoEngine.git` from your terminal interface of choice
2. Navigate to *LeoEngine/*
3. Run `git submodule init`
4. Run `git submodule update`
5. Navigate to *LeoEngine/tools/\<your operating system\>/*

**IF ON WINDOWS** run *pre_first_build.bat*.

6. Run the build script located within

If you ran the build script from the terminal, you should now be in the build directory. Otherwise, you can find the built library files in *LeoEngine/build/*
