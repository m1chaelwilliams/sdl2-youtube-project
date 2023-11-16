#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "scene.h"
#include "mainscene.h"
#include "scenemanager.h"
#include "contentmanager.h"

class App {
private:
    // temp
    SDL_Texture* texture;
    // end temp

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

    std::vector<SDL_Texture*> texture_pool;

    SceneManager sm;
    ContentManager cm;
};

#endif