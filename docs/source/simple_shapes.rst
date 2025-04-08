Simple Shapes
=============

This guide will show you how to draw simple shapes on the screen using a minimal Leo Engine project and a basic derivation of the ``Scene`` class.

Services
--------

In the Leo Engine, a service is little more than a global class containing a number of themed helper functions and private member objects that store related persistent data.

There are a total of six services: audio, events, graphics, input, logger, and saver. Each of these is intended to handle one task for you. Which task it's meant to handle should be fairly obvious from its name.

The ``Services`` singleton acts as an interface to each of these services. For example, retrieving the graphics service is done like so: ``Services::get()->getGraphics()``.

In this guide we will only be using the graphics service.

To be finished.

