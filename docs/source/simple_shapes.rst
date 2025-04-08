Simple Shapes
=============

This guide will show you how to draw simple shapes on the screen using a minimal Leo Engine project and a basic derivation of the ``Scene`` class.

Services
--------

In the Leo Engine, a service is little more than a global class containing a number of themed helper functions and private member objects that store related persistent data.

There are a total of six services: audio, events, graphics, input, logger, and saver. Each of these is intended to handle one task for you. Which task it's meant to handle should be fairly obvious from its name.

The ``Services`` singleton acts as an interface to each of these services. For example, retrieving the graphics service is done like so: ``Services::get()->getGraphics()``.

In this guide we will only be using the graphics service.

Supported Shapes
----------------

The Leo Engine has three built-in shapes:

* ``Circle``
* ``Rectangle``
* ``Line``

However, of these three, only the ``Rectangle`` and ``Line`` can be drawn with Leo Engine functions. Support for drawing circles may or may not be added in the future.

Scenes and Drawing
------------------

The `Game` class, like many Leo Engine classes, has an ``update`` method and a ``draw`` method. These don't do anything other than calling the current scene's ``update`` and ``draw`` functions. So, anything we want to be drawn on the screen must be drawn during a scene's draw method.

So, let's start by creating a new class derived from ``Scene``.

.. code-block:: C++
    
    #include "LeoEngine/Scene.hpp"
    
    class MyScene : public LeoEngine::Scene
    {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        // we don't care about the update function right now, but it's good to know it's there!
        virtual void update() override {}

        virtual void draw() override
        {
            // shape drawing will happen here
        }
    }

Drawing a Rectangle
-------------------

Let's draw a rectangle. The window we created in :doc:`quickstart` was 512pt by 512pt. Let's try and place our rectangle in the center.

.. code-block:: C++

    #include "LeoEngine/Rectangle.hpp"
    #include "LeoEngine/Colour.hpp"

    ...

        virtual void draw() override
        {
            LeoEngine::Rectangle myRectangle(128, 128, 256, 256);
            LeoEngine::Colour myColour(255, 255, 255, 255);
        }

    ...

First, we included the Leo Engine ``Rectangle`` type. While it's not necessary, using an instance of ``Rectangle`` makes rectangle drawing code easier to read. This ``Rectangle`` constructor takes four arguments: x, y, width, and height. x and y are the coordinates of the top-left corner of the rectangle, while width and height are its dimensions.

Then, we created a Leo Engine ``Colour`` object. This colour is a solid white. Leo Engine uses standard RGBA codes, with values ranging from 0 to 255.

Now let's actually draw it! We'll use the graphics service's ``drawRectangle`` function.

.. code-block:: C++
    
    #include "LeoEngine/Services.hpp"
    #include "LeoEngine/Graphics.hpp"

    ...

        LeoEngine::Services::get()->getGraphics().drawRectangle(myColour, true, myRectangle);

    ...

Make sure you include both *Services.hpp* and *Graphics.hpp*.

There are a couple of things happening in this one line. First, ``LeoEngine::Services::get()`` gets the Services singleton from Leo Engine. Then, ``->getGraphics()`` retrieves the graphics service. Lastly, ``.drawRectangle(myColour, myRectangle)`` draws a rectangle with the coordinates and dimensions of ``myRectangle`` and the colour specified in myColour. The boolean parameter tells the graphics service whether or not it should fill in the rectangle. In this case, we should get a filled, solid white rectangle.

To be completed...

