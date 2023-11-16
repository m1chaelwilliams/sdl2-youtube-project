#include "scene.h"

#ifdef DEBUG
#include <iostream>
#endif

Scene::Scene(
    SDL_Renderer* renderer_ptr, 
    SceneManager* sm, 
    ContentManager* cm,
    EventHandler* eh
) : renderer_ptr(renderer_ptr), 
    sm(sm), 
    cm(cm),
    eh(eh)
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

void Scene::on_load() {}
void Scene::on_unload() {}
void Scene::update() {}
void Scene::draw() {}