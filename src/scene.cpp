#include "scene.h"

#include "debugutils.h"

IScene::IScene(
    SDL_Renderer* renderer_ptr, 
    SceneManager* sm, 
    ContentManager* cm,
    EventHandler* eh
) : renderer_ptr(renderer_ptr), 
    sm(sm), 
    cm(cm),
    eh(eh)
{
    LOG("Scene object created!");
}

IScene::~IScene() {
    LOG("Scene object destructed!");
}