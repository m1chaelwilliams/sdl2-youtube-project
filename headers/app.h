#ifndef APP_H
#define APP_H

#ifdef DEBUG
#include "debugutils.h"
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "scene.h"
#include "mainscene.h"
#include "testscene.h"
#include "eventhandler.h"
#include "scenemanager.h"
#include "contentmanager.h"

class App {
private:
    bool running;
    int width, height;
    const char* title;

    bool init();
    void on_load();
    void on_unload();
    void update();
    void draw();
public:
    App(
        int width = 600,
        int height = 400,
        const char* title = "App"
    );
    ~App();
    int run();
private:
    SDL_Window* window_ptr;
    SDL_Renderer* renderer_ptr;

    SceneManager sm;
    ContentManager cm;
    EventHandler eh;
};

#endif