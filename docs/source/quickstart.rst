Quickstart
==========

This page will outline the creation of a minimal Leo Engine project. All Leo Engine projects consists of a ``Engine`` object and a ``Game`` object containing any number of ``Scene`` objects.

Creating a Leo Engine Project
-----------------------------

For the purposes of this guide everything we do will take place in our main function. We'll begin by including *EngineSettings.hpp*.

.. code-block:: C++

    #include "LeoEngine/EngineSettings.hpp"

Next, we'll create an ``EngineSettings`` object.

.. code-block:: C++

    ...

    int main(int argc, char *argv[])
    {
        LeoEngine::EngineSettings myEngineSettings;
    }

Note that all Leo Engine classes and functions exist within the ``LeoEngine`` namespace.

An ``EngineSettings`` object is passed to the ``Engine`` constructor. It provides the engine with details about your application, like the properties of the window that should be created for it. These details are stored as public data members within the object, so we can easily set them with the ``.`` and ``=`` operators. Any of these properties can be ignored and will be default initialized. As such, you *can* provide an unmodified ``EngineSettings`` object to the ``Engine`` constructor, though this would be odd thing to do.

.. code-block:: C++

    ...

        myEngineSettings.defaultWindowWidth = 512;
        myEngineSettings.defaultWindowHeight = 512;
        myEngineSettings.defaultFullscreen = false;
        myEngineSettings.defaultWindowTitle = "My Leo Engine Window";

    ...

Once all desired engine settings have been set, we can create an ``Engine`` object. Ensure you also include *Engine.hpp*

.. code-block:: C++

    #include "LeoEngine/Engine.hpp"

    ...

        LeoEngine::Engine myEngine(myEngineSettings);

    ...

Once the ``Engine`` object has been created, the ``EngineSettings`` object is no longer useful. You can still modify the properties it set, but changing them in the ``EngineSettings`` object will do nothing.

Next, we'll create a ``Game`` object. The ``Game`` object holds all of the ``Scene`` objects that make up your game. The ``Scene`` class will be explained in detail in another guide.

.. code-block:: C++

    #include "LeoEngine/Game.hpp"

    ...

        LeoEngine::Game myGame;

    ...

With this, we now have a complete Leo Engine project! To run our newly created game, we need to add one final line.

.. code-block:: C++

    ...

    myEngine.runGame(myGame);

    ...

Building the Project with CMake
-------------------------------

The 'official' way to build a Leo Engine project is with `CMake <https://www.cmake.org>`_.

As an example, the project structure that I've used in the past is as follows:

* a **lib** directory for libraries
  * the LeoEngine library
* a **src** directory for source files
  * *main.cpp*
* *CMakeLists.txt*

Then, you can populate *CMakeLists.txt* with something like this:

.. code-block:: cmake

    cmake_minimum_required(VERSION 3.11)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    project(MyGame)

    add_subdirectory(lib/LeoEngine)

    file(GLOB SOURCES src/*)

    add_executable(MyGame ${SOURCES})

    target_link_libraries(MyGame PRIVATE LeoEngine)
    target_include_directories(MyGame PRIVATE lib/LeoEngine/include)

If you're on MacOS it may be useful to include an *Info.plist* file as well, as it allows you to configure SDL's ``GetBasePath()`` and ``GetPrefPath()`` functions in a more Mac friendly way. I'll leave that up to you to figure out.

Now, you can run ``cmake . -B build`` from the project's root directory. This will create the **build** directory and fill it with build files: a Visual Studio project on Windows or a Makefile on Unix.

That's about all there is to know about building a Leo Engine project.

Next, I'd recommend checking out :doc:`scene`.

