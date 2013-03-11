GL++ (glpp)
===========

OpenGL C++ Wrapper provides a C++ interface for the OpenGL API. The wrapper tries to expose all the logical objects of OpenGL standard to C++ native objects. This is not a graphics library, thus you will not find any assets manipulation or math functionality. However the library is designed to be easily coupled with an external math library like [glm](http://glm.g-truc.net/) or an assets manipulation library like [assimp](http://assimp.sourceforge.net/).


Build
=====

GL++ uses [CMake](http://www.cmake.org/) build system. To continue you must ensure that you have the cmake installed on your system. It is preferred to build project in a sub-folder than doing it directly in tree.

    mkdir build
    cd build
    cmake ..
    make

Documentation
=============

[Doxygen](http://www.stack.nl/~dimitri/doxygen) is used for in-code documentation. You can build documentation files by simply running doxygen on the top folder where Doxyfile resides.

Request For Help
================

OpenGL API is quite big, has a lot of history and this is reflected in many domains. Studing the API and trying to find the best C++ representation requires a lot of effort. Any person who can help on this procedure can be useful for this project. Even jannitoring is also welcome.

Please contact me if you want to contribute.

