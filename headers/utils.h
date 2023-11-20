#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

namespace se {
    bool intersects(const SDL_Rect& rect1, const SDL_Rect& rect2);
}

#endif