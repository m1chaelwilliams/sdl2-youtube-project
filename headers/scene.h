#ifndef ISCENE_H
#define ISCENE_H

#include <SDL2/SDL.h>
#include "scenemanager.h"
#include "contentmanager.h"
#include "eventhandler.h"

class IScene {
    public:
        IScene(
            SDL_Renderer* renderer_ptr, 
            SceneManager* sm, 
            ContentManager* cm,
            EventHandler* eh
        );
        virtual ~IScene();
        virtual void on_load() = 0;
        virtual void on_unload() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
    protected:
        SceneManager* sm;
        ContentManager* cm;
        EventHandler* eh;
        SDL_Texture* texture;
        SDL_Renderer* renderer_ptr;
};

#endif