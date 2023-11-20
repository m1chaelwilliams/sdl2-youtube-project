#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>

namespace se {
    class IScene;
}

namespace se::managers {
    class SceneManager {
        public:
            SceneManager();
            ~SceneManager();

            void add_scene(int scene_id, IScene* scene);
            void remove_scene(int scene_id);
            IScene* pop(int scene_id);
            IScene* get_scene();
            void set_scene(int scene_id);
        private:
            std::map<int, IScene*> scenes;

            int active_scene;
            IScene* active_scene_ptr;
    };
}

#endif