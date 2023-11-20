#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "eventhandler.h"
#include "scenemanager.h"
#include "contentmanager.h"
#include "musicplayer.h"

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

    SceneManager* _get_scene_manager() {return &sm;}
    ContentManager* _get_content_manager() {return &cm;}
    EventHandler* _get_event_handler() {return &eh;}
    MusicPlayer* _get_music_player() {return &mp;}
    SDL_Renderer* _get_renderer() {return renderer_ptr;}
protected:
    SDL_Window* window_ptr;
    SDL_Renderer* renderer_ptr;

    SceneManager sm;
    ContentManager cm;
    EventHandler eh;
    MusicPlayer mp;
};

#endif