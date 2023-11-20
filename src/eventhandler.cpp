#include "eventhandler.h"

#include "debugutils.h"

using namespace se::managers;

EventHandler::EventHandler() {}
EventHandler::~EventHandler() {
    LOG("Destructing EventHandler...");
}

void EventHandler::poll_events() {
    events.clear();
    keys_pressed.clear();

    std::vector<SDL_Keycode> keys_to_remove;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        events.push_back(e);

        if (e.type == SDL_KEYDOWN && !is_key_down(e.key.keysym.sym)) {
            keys_pressed.push_back(e.key.keysym.sym);
            keys_held.push_back(e.key.keysym.sym);
        }

        if (e.type == SDL_KEYUP && is_key_down(e.key.keysym.sym)) {
            keys_to_remove.push_back(e.key.keysym.sym);
        }
    }

    for (const auto& key : keys_to_remove) {
        keys_held.erase(std::remove(keys_held.begin(), keys_held.end(), key), keys_held.end());
    }
}

bool EventHandler::is_key_down(SDL_Keycode key) const {
    for (auto& key_iter : keys_held) {
        if (key_iter == key) {
            return true;
        }
    }
    return false;
}

bool EventHandler::is_key_pressed(SDL_Keycode key) const {
    for (auto& key_iter : keys_pressed) {
        if (key_iter == key) {
            return true;
        }
    }
    return false;
}

bool EventHandler::is_close_requested() const {
    for (auto& event : events) {
        if (event.type == SDL_QUIT)
            return true;
    }
    return false;
}