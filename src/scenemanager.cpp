#include "scenemanager.h"
#include "scene.h"

#include "debugutils.h"

using namespace se;
using namespace se::managers;

SceneManager::SceneManager() {}
SceneManager::~SceneManager() {

    LOG("Destructing Scene Manager...");

    for (auto& scene : scenes) {
        LOG("Destroying scene: " << scene.first);

        delete scene.second;
    }
    scenes.clear();
}

void SceneManager::add_scene(int scene_id, IScene* scene) {
    remove_scene(scene_id);
    scenes[scene_id] = scene;

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
    if (scenes.find(scene_id) != scenes.end()) {
        delete scenes[scene_id];
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
    if (scenes.find(scene_id) != scenes.end()) {
        IScene* scene = scenes[scene_id];
        scenes.erase(scene_id);
        return scene;
    }
    return nullptr;
}

IScene* SceneManager::get_scene() {
    return scenes[active_scene];
}

void SceneManager::set_scene(int scene_id) {
    if (scenes.find(scene_id) != scenes.end()) {
        active_scene = scene_id;
    }
}