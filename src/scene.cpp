#include "scene.h"

#include "debugutils.h"

IScene::IScene(
    App* app
) : app(app)
{
    cm = this->app->_get_content_manager();
    sm = this->app->_get_scene_manager();
    eh = this->app->_get_event_handler();
    mp = this->app->_get_music_player();
    renderer_ptr = this->app->_get_renderer();

    LOG("Scene object created!");
}

IScene::~IScene() {
    LOG("Scene object destructed!");
}