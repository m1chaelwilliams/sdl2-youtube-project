#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <SDL2/SDL.h>
#include "scene.h"
#include <iostream>

class TestScene : public Scene {
public:
    TestScene(
        SDL_Renderer* renderer_ptr,
        SceneManager* sm,
        ContentManager* cm,
        EventHandler* eh
    ) : Scene(renderer_ptr, sm, cm, eh) {}
    virtual ~TestScene() {
        std::cout << "test scene destructed!" << std::endl;
    }
};

#endif