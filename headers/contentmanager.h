#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class ContentManager {
public:
    ContentManager() {}
    ~ContentManager();

    SDL_Texture* load_texture(
        SDL_Renderer* renderer_ptr, 
        const char* filename, 
        const char* name = ""
    );
    SDL_Texture* load_texture(
        SDL_Renderer* renderer_ptr, 
        SDL_Surface* surf, 
        const char* filename,
        bool free_surf = false
    );
    SDL_Texture* get_texture(const char* key);
    SDL_Rect get_rect(const char* filename);
private:
    std::map<std::string, SDL_Texture*> textures;
};

#endif