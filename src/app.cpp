#include "app.h"

#define INIT_SUCCESS true
#define INIT_FAIL false

void App::on_load() {
    sm.add_scene(0, new MainScene(renderer_ptr, &sm, &cm, &eh));
    sm.set_scene(0);

    sm.get_scene()->on_load();
}

void App::on_unload() {
    sm.get_scene()->on_unload();
}

void App::update() {
    eh.poll_events();
    if (eh.is_close_requested() || eh.is_key_pressed(SDLK_q)) {
        running = false;
    }

    sm.get_scene()->update();
}

void App::draw() {
    SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255);
    SDL_RenderClear(renderer_ptr);

    sm.get_scene()->draw();

    SDL_RenderPresent(renderer_ptr);

    SDL_Delay(16);
}

int App::run() {
    LOG("Initializing...");

    if (!init()) {
        return -1;
    }

    LOG("Initializing successful!");
    LOG("--------------------");
    LOG("`on_load` executing...");

    on_load();

    LOG("`on_load` successful!");
    LOG("--------------------");
    LOG("Enter main loop...");

    while (running) {
        update();
        draw();
    }

    LOG("Exiting main loop...");
    LOG("--------------------");
    LOG("`on_unload` executing...");

    on_unload();

    LOG("`on_unload` successful!");
    LOG("--------------------");

    return 0;
}

// don't touch !!!

bool App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return INIT_FAIL;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        return INIT_FAIL;
    }

    if (TTF_Init() < 0) {
        return INIT_FAIL;
    }

    window_ptr = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window_ptr) {
        return INIT_FAIL;
    }

    renderer_ptr = SDL_CreateRenderer(
        window_ptr,
        -1,
        0
    );

    if (!renderer_ptr) {
        return INIT_FAIL;
    }

    return INIT_SUCCESS;
}

App::App(
    int width,
    int height,
    const char* title
)
:   width(width),
    height(height),
    title(title),
    window_ptr(nullptr),
    renderer_ptr(nullptr),
    running(true)
{
    LOG("--------------------");
    LOG("App constructed!");
}

App::~App() {
    LOG("--------------------");
    LOG("App Destructing...");

    cm.free_all();

    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();
    
    LOG("Quit SDL2");

    IMG_Quit();

    LOG("Quit SDL2_IMG");

    TTF_Quit();

    LOG("Quit SDL2_TTF");
}