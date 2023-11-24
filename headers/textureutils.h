#ifndef TEXTUREUTILS_H
#define TEXTUREUTILS_H

#include <SDL2/SDL.h>

namespace se {
    struct TextureData {
        SDL_Texture* texture_data;
        int w;
        int h;
    };
}

#endif