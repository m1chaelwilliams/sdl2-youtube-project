#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>

class Scene;

class SceneManager {
    public:
        SceneManager();
        ~SceneManager();

        void add_scene(int scene_id, Scene* scene);
        void remove_scene(int scene_id);
        Scene* pop(int scene_id);
        Scene* get_scene();
        void set_scene(int scene_id);
    private:
        std::map<int, Scene*> scenes;

        int active_scene;
};

#endif