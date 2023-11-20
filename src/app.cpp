#include "app.h"
#include "debugutils.h"
#include "scene.h"

using namespace se;
using namespace se::managers;


#define INIT_SUCCESS true
#define INIT_FAIL false

void IApp::close() {
    running = false;
}

int IApp::run() {
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
        // polling events and checking quit request
        event_handler.poll_events();
        if (event_handler.is_close_requested()) {
            close();
        }

        on_update();
        on_draw();
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

bool IApp::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return INIT_FAIL;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        return INIT_FAIL;
    }

    if (TTF_Init() < 0) {
        return INIT_FAIL;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
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

IApp::IApp(
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

IApp::~IApp() {
    LOG("--------------------");
    LOG("App Destructing...");

    content_manager.free_all();

    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();
    
    LOG("Quit SDL2");

    IMG_Quit();

    LOG("Quit SDL2_IMG");

    TTF_Quit();

    LOG("Quit SDL2_TTF");

    Mix_CloseAudio();

    LOG("Quit SDL2_Mixer");
}