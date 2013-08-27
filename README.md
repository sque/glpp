GL++ (glpp)
===========

OpenGL C++ Wrapper provides a C++ interface for the OpenGL API. The wrapper tries to expose all the logical objects of OpenGL standard to C++ native objects. This is not a graphics library, thus you will not find any assets manipulation or math functionality. However the library is designed to be easily coupled with an external math library like [glm](http://glm.g-truc.net/) or an assets manipulation library like [assimp](http://assimp.sourceforge.net/).

The major keypoints of GL++ API are:
* Do not introduce new semantics.
* Do not hide steps, by creating all-in-one functions.
* Try to use common names with OpenGL C API to avoid confusion.
* Use C++ language to represent OOP semantics (e.g. [OpenGL objects](http://www.opengl.org/wiki/OpenGL_Object) )


Comparison of using OpenGL C API and GL++
-----------------------------------------

### Creating a program and loading some shader files

OpenGL C API
```C
// Prototype of a user function to load shader from file
int loadshader(char * filename, GLchar** ShaderSource, unsigned long* len);

GLuint vertexShader, fragmentShader, ProgramObject;
GLchar* shaderSource;
int shaderSourceLen;
    
vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
loadshader("shaderfile.vert", &shaderSource, &shaderSourceLen)
glShaderSource(vertexShader, 1, &shaderSource, &shaderSourceLen)
glCompileShader(vertexShader)

fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
loadshader("shaderfile.frag", &shaderSource, &shaderSourceLen)
glShaderSource(vertexShader, 1, &shaderSource, &shaderSourceLen)
glCompileShader(vertexShader)

ProgramObject = glCreateProgram();
glAttachShader(ProgramObject, vertexShaderObject);
glAttachShader(ProgramObject, fragmentShaderObject);

glLinkProgram(ProgramObject);
```
Same on GL++

```cpp
glpp::shared_program_t pprog;

pprog = new glpp::program();
pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, "shaderfile.vert"));
pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, "shaderfile.frag"));
pprog->build();
pprog->use();
```

Build
=====

GL++ uses [CMake](http://www.cmake.org/) build system. To continue you must ensure that you have the cmake installed on your system, and all the needed libraries.

To build the library you will need:
* OpenGL headers/libraries - usually provided by your graphics driver
* [FreeGLUT](http://freeglut.sourceforge.net)
* [GLEW](http://glew.sourceforge.net/)

To build the examples you will need also:
* [GLM](http://glm.g-truc.net/)
* [FreeImage](http://freeimage.sourceforge.net/)
* [Boost](http://www.boost.org)
* [Assimp](http://assimp.sourceforge.net)

It is preferred to build project in a sub-folder than doing it directly in tree.

```bash
mkdir build
cd build
cmake ..
make
```

Documentation
=============

[Doxygen](http://www.stack.nl/~dimitri/doxygen) is used for in-code documentation. You can build documentation files by simply running doxygen on the top folder where Doxyfile resides.

Request For Help
================

OpenGL has a big API, with a lot of history and this is reflected in many domains. Studing the API and trying to find the best C++ representation requires a lot of effort. Any person who can help on this procedure can be useful for this project. Even jannitoring is also welcome.

Please [contact me](https://github.com/sque/glpp) if you want to contribute.

