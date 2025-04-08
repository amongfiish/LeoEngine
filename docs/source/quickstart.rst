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

Building the Project
--------------------

TBA

