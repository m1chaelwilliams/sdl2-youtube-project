#include "scene.h"

#ifdef DEBUG
#include <iostream>
#endif

Scene::Scene(
    SDL_Renderer* renderer_ptr, 
    SceneManager* sm, 
    ContentManager* cm
) : renderer_ptr(renderer_ptr), 
    sm(sm), 
    cm(cm) 
{
#ifdef DEBUG
    std::cout << "Scene object created!" << std::endl;
#endif
}
Scene::~Scene() {
#ifdef DEBUG
    std::cout << "Scene object destructed!" << std::endl;
#endif
}

void Scene::on_load() {
    texture = cm->load_texture(renderer_ptr, "assets/player_static.png", "player");
}
void Scene::on_unload() {}
void Scene::update() {}
void Scene::draw() {
    SDL_SetRenderDrawColor(renderer_ptr, 255, 0, 0, 255);
    SDL_RenderClear(renderer_ptr);

    SDL_Rect rect{10,10,100,100};
    SDL_Rect srect{0,0,8,16};

    SDL_SetRenderDrawColor(renderer_ptr, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer_ptr, &rect);

    SDL_RenderCopy(renderer_ptr, texture, &srect, &rect);
}