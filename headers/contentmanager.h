#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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

    // fonts
    TTF_Font* load_font(const char* filename, int size, const char* name = "");
    TTF_Font* get_font(const char* name);

    void free_all();
private:
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};

#endif