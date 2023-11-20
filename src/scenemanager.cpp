#include "scenemanager.h"
#include "scene.h"

#include "debugutils.h"

using namespace se;
using namespace se::managers;

SceneManager::SceneManager() {
    active_scene = -1;
    active_scene_ptr = nullptr;

    LOG("Created Scene Manager!");
}
SceneManager::~SceneManager() {

    LOG("Destructing Scene Manager...");

    active_scene_ptr->on_scene_exit();

    for (auto& scene : scenes) {
        LOG("Destroying scene: " << scene.first);
        scene.second->on_unload();
        delete scene.second;
    }
    scenes.clear();
}

void SceneManager::add_scene(int scene_id, IScene* scene) {
    // if scene alr exists, remove it
    remove_scene(scene_id);
    scenes[scene_id] = scene;
    
    scene->on_load();

#ifdef DEBUG
    LOG("Added scene: " << scene_id);

    LOG("Scenes in App:");
    for (const auto& scene : scenes) {
        LOG(scene.first);
    }
#endif
}

void SceneManager::remove_scene(int scene_id) {
    LOG("Removing scene: ");
    
    if (!active_scene_ptr) {
        return;
    }

    auto it = scenes.find(scene_id);
    if (it != scenes.end()) {

        if (it->first == active_scene) {
            active_scene_ptr->on_scene_exit();
        }

        it->second->on_unload();
        delete it->second;
        scenes.erase(scene_id);
    }

    LOG("Remaining scenes");
#ifdef DEBUG
    for (const auto& scene : scenes) {
        LOG(scene.first);
    }
#endif
}

IScene* SceneManager::pop(int scene_id) {
    auto it = scenes.find(scene_id);

    if (it != scenes.end()) {
        IScene* scene = it->second;
        scenes.erase(scene_id);
        return scene;
    }
    return nullptr;
}

IScene* SceneManager::get_scene() {
    return active_scene_ptr;
}

void SceneManager::set_scene(int scene_id) {
    LOG("Set Scene! " << scene_id);

    if (active_scene_ptr) {
        LOG("EXITING PREVIOUS SCENE");
        active_scene_ptr->on_scene_exit();
    }

    auto it = scenes.find(scene_id);
    if (it != scenes.end()) {
        active_scene = scene_id;
        active_scene_ptr = it->second;

        LOG("ENTERING NEW SCENE");
        active_scene_ptr->on_scene_enter();
    }
}