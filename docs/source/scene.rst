Scenes
======

A Leo Engine ``Scene`` is an abstract class that holds a collection of ``Object`` instances and anything else neccessary to create a single 'section' of a game. This 'section' could be the gameplay loop of an arcade game, a main menu, or a loading screen.

You can check out :doc:`scene` for detailed documentation of the ``Scene`` class.

Creating a Scene
----------------

To create a scene, you can't simply initialize a new ``Scene`` object, as it's an abstract class. Instead, you must define a new child of the ``Scene`` class.

If you are making an arcade game with only one kind of gameplay experience, you might make a new child of the ``Scene`` class called ``SceneGame``. Then, in its constructor, or an overridden ``update`` function, you'd define the behaviour necessary for the scene to function. In the case of our arcade game, you might create the player in the constructor and then spawn enemies every few frames in the update function.

The base ``Scene`` class is very simple, so it's up to you how complex or simple your scenes are.

Using a Scene
-------------

The ``Game`` class has a ``SceneCollection`` member object, which can be used to store any scenes you want your game to have. You can retrieve this object with the ``Game::getSceneCollection`` function.

You can add a scene to the game with the ``SceneCollection::addScene`` function. This is a template function which takes no arguments other than the template type parameter. It will construct a new scene of the provided type for you, and return an integer 'ID'. This ID can be used to set the current scene with the ``SceneCollection::setCurrentScene`` or ``SceneCollection::fadeToScene`` functions.

It's also possible to prompt a scene change without access to a ``SceneCollection`` object by broadcasting an instance of ``EventSceneChange``. This event, along with others, will be explained in detail in another guide.

And so concludes this very wordy rundown of the basic function of scenes.

Next, I'd recommend checking out :doc:`simple_shapes`.

