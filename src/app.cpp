#include "app.h"

#define INIT_SUCCESS true
#define INIT_FAIL false

#ifdef DEBUG
#include <iostream>
#endif

void App::on_load() {
    sm.add_scene(0, new Scene(renderer_ptr, &sm, &cm));
    sm.set_scene(0);

    sm.get_scene()->on_load();
}
void App::on_unload() {
    sm.get_scene()->on_unload();
}
void App::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
            break;
        }
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_q) {
                running = false;
                break;
            }
        }
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
#ifdef DEBUG
    std::cout << "Initializing..." << std::endl;
#endif

    if (!init()) {
        return -1;
    }

#ifdef DEBUG
    std::cout << "Initializing successful!" << std::endl;
#endif

#ifdef DEBUG
    std::cout << "`on_load` executing..." << std::endl;
#endif

    on_load();

#ifdef DEBUG
    std::cout << "`on_load` successful!" << std::endl;
    std::cout << "Enter main loop..." << std::endl;
#endif

    while (running) {
        update();
        draw();
    }

#ifdef DEBUG
    std::cout << "Exiting main loop..." << std::endl;
    std::cout << "`on_unload` executing..." << std::endl;
#endif

    on_unload();

#ifdef DEBUG
    std::cout << "`on_unload` successful!" << std::endl;
#endif

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
#ifdef DEBUG
    std::cout << "App constructed!" << std::endl;
#endif
}

App::~App() {
#ifdef DEBUG
    std::cout << "App Destructing..." << std::endl;
#endif
    for (auto& texture : texture_pool) {
        SDL_DestroyTexture(texture);
    }
    texture_pool.clear();

    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();
    IMG_Quit();
#ifdef DEBUG
    std::cout << "App destruction complete!" << std::endl;
#endif
}