Setup
=====

Preparation
-----------

Leo Engine is built with `CMake <https://cmake.org>`_. Install it before continuing.

If you're on Windows, you'll also need a copy of Visual Studio and its C++ build tools.

Every other requirement is included within the repository. You can acquire the LeoEngine source from github by executing ``git clone https://github.com/amongfiish/LeoEngine.git``.

Run the **pre_first_build** tool specific to your operating system. This can be found in the **tools/<os>** folder. This tool populates the repository's submodule folders and downloads some additional things required by the SDL extension libraries.

Building
--------

Building Leo Engine is as simple as building any other CMake application. In the repository's root directory, execute ``cmake . -B build``. Then, move into the **build** folder.

If you're on a Unix platform, run ``make``. A shared object file will be created within the **build** directory.

If you're on Windows, you'll have to open the newly created Visual Studio project and build it from within the application.

