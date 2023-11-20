# App Class (app.h, app.cpp)

## Introduction
The `IApp` class is the main abstract class that encapsulates the entire program. It handles the construction, lifetime, and destruction.

## Abstract Methods

There are 4 abstract methods in `IApp`:

```
void on_load();
```
Called after construction and initialization of internal dependencies.

```
void on_unload();
```
Called after main lifetime, before destruction of internal .dependencies.

```
void on_update();
```
Called every frame during main lifetime.

```
void on_draw();
```
Called every frame during main lifetime.

**Note** updating in `on_update` and drawing in `on_drawing` is totally optional. They are split up for purely semantic reasons. Rendering a scene is exposed to the user via raw `SDL2` function calls.

## Life Cycle

As mentioned before, the `IApp` class takes care of the initialization, maintainence, and destruction.

#### - Construction
        - Does nothing as of right now
#### - Lazy initialization
        - Calls `run` method in charge of executing program
        - intializes dependencies
        - calls `on_load`
        - enters game loop
        - calls `update` and `draw` (and other minor tasks) every frame
        - calls `on_unload`
#### - Destructs
        - Frees dynamically allocated resources from `ContentManager`
        - quits all dependencies