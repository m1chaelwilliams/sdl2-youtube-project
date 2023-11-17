#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>

class EventHandler {
public:
    EventHandler();
    ~EventHandler();
    void poll_events();
    bool is_key_down(SDL_Keycode key) const;
    bool is_key_pressed(SDL_Keycode key) const;
    bool is_close_requested() const;
private:
    std::vector<SDL_Keycode> keys_pressed;
    std::vector<SDL_Keycode> keys_held;
    std::vector<SDL_Event> events;
};

#endif