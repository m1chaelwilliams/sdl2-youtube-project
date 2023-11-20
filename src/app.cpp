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

    if (!(init() && create_display() && create_renderer())) {
        return -1;
    }
    app_initialized = true;

    LOG("Initializing successful!");

    LOG("`on_load` executing...");

    on_load();

    LOG("`on_load` successful!");

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
    return INIT_SUCCESS;
}

bool IApp::create_display() {
    window_ptr = SDL_CreateWindow(
        title,
        x,
        y,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window_ptr) {
        return INIT_FAIL;
    }
    return INIT_SUCCESS;
}

bool IApp::create_renderer() {
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
    const char* title,
    int window_pos_x,
    int window_pos_y
)
:   width(width),
    height(height),
    title(title),
    window_ptr(nullptr),
    renderer_ptr(nullptr),
    running(true),
    app_initialized(false),
    x(window_pos_x),
    y(window_pos_y),
    icon_surface(nullptr)
{
    LOG("--------------------");
    LOG("App constructed!");
}

IApp::~IApp() {
    LOG("--------------------");
    LOG("App Destructing...");

    LOG("FREEING ICON");
    if (icon_surface) {
        SDL_FreeSurface(icon_surface);
    }
    LOG("ICON FREED");

    content_manager.free_all();

    LOG("DESTROYING RENDERER...");
    SDL_DestroyRenderer(renderer_ptr);
    LOG("DESTROYING WINDOW...");
    SDL_DestroyWindow(window_ptr);
    LOG("QUITTING SDL2...")
    SDL_Quit();
    
    LOG("Quit SDL2");

    IMG_Quit();

    LOG("Quit SDL2_IMG");

    TTF_Quit();

    LOG("Quit SDL2_TTF");

    Mix_CloseAudio();

    LOG("Quit SDL2_Mixer");
}

void IApp::resize(int width, int height) {
    this->width = width;
    this->height = height;

    if (app_initialized) {
        SDL_SetWindowSize(window_ptr, this->width, this->height);
    }
}

void IApp::set_icon(const char* filename) {
    LOG("SETTING ICON...");
    if (icon_surface) {
        LOG("FREEING PREVIOUS ICON");
        SDL_FreeSurface(icon_surface);
        icon_surface = nullptr;
    }

    LOG("ALLOCATING ICON");
    icon_surface = IMG_Load(filename);

    LOG("SETTING ICON");
    SDL_SetWindowIcon(window_ptr, icon_surface);
}

void IApp::set_title(const char* title) {
    this->title = title;

    if (app_initialized) {
        SDL_SetWindowTitle(window_ptr, title);
    }
}

void IApp::set_window_position(int x, int y) {
    SDL_SetWindowPosition(window_ptr, x, y);
}

void IApp::center_window() {
    set_window_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

int IApp::get_width() const {return width;}
int IApp::get_height() const {return height;}
int IApp::get_window_pos_x() const {return x;}
int IApp::get_window_pos_y() const {return y;}
const char* IApp::get_title() const {return title;}