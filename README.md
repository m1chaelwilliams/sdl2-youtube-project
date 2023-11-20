# Sphere's SDL2 Engine (Version 0.1)

A simple, game engine written on top of SDL and other SDL tools. Designed to make game development easier through a management systems and object-oriented design.

## Dependencies
 - SDL2
 - SDL_image
 - SDL_TTF
 - SDL_mixer

## Compatibility

As of writing this, the engine has only been tested on Windows. However, assuming there are no issues with SDL2 on other operating systems, none of the code here is platform specific. This **should** work on MacOS and Linux, but it is not at all guaranteed. Use at your own risk!

## Install

Clone this repository to your device. 
Execute `make library` or `make debug` (for debug build).
This will produce a "libse.a" file in "build".
I strongly recommend using a debug build when writing your game.
Download all the dependencies and set them up accordingly.

A typicall folder structure would look like:

```
root:
->build
--> <all_your_dlls>
->headers
--> <all_your_headers>
->include
--> <all_header_files>
->lib
--> <all_your_libs.a>
->src
-->main.cpp
->Makefile
```

## Compiling your program

Execute this command:

```
g++ main.cpp -o projectname -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
```

Depending on your project structure, this command can vary quite a bit. As long as it looks something like this:

```
<compiler> <source file(s)> -o <project name> <include dir> <lib dir> <libs>
```

**NOTE** against the static lib **first**, before any of the other libraries.

# Documentation (WIP)

The documentation can be found [here](documentation/app.md).