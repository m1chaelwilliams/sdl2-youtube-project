#ifndef APP_H
#define APP_H

#include "debugutils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "scene.h"
#include "eventhandler.h"
#include "scenemanager.h"
#include "contentmanager.h"

class App {
private:
    bool running;
    int width, height;
    const char* title;

    bool init();
protected:
    virtual void on_load() = 0;
    virtual void on_unload() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    void close();
public:
    App(
        int width = 600,
        int height = 400,
        const char* title = "App"
    );
    ~App();
    int run();
protected:
    SDL_Window* window_ptr;
    SDL_Renderer* renderer_ptr;

    SceneManager sm;
    ContentManager cm;
    EventHandler eh;
};

#endif