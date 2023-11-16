#include "scenemanager.h"
#include "scene.h"

#ifdef DEBUG
#include <iostream>
#endif

SceneManager::SceneManager() {}
SceneManager::~SceneManager() {
#ifdef DEBUG
        std::cout << "Destructing Scene Manager" << std::endl << std::endl;
#endif
    for (auto& scene : scenes) {
#ifdef DEBUG
        std::cout << "Destroying scene: " << scene.first << std::endl;
#endif
        delete scene.second;
    }
    scenes.clear();
}

void SceneManager::add_scene(int scene_id, Scene* scene) {
    remove_scene(scene_id);
    
    scenes[scene_id] = scene;
}

void SceneManager::remove_scene(int scene_id) {
    if (scenes.find(scene_id) != scenes.end()) {
        delete scenes[scene_id];
        scenes.erase(scene_id);
    }
}

Scene* SceneManager::pop(int scene_id) {
    if (scenes.find(scene_id) != scenes.end()) {
        Scene* scene = scenes[scene_id];
        scenes.erase(scene_id);
        return scene;
    }
    return nullptr;
}

Scene* SceneManager::get_scene() {
    return scenes[active_scene];
}

void SceneManager::set_scene(int scene_id) {
    if (scenes.find(scene_id) != scenes.end()) {
        active_scene = scene_id;
    }
}