#include "scene.h"

#include "debugutils.h"

using namespace se;

IScene::IScene(
    IApp* app
) : app(app)
{
    LOG("Scene object created!");
}

IScene::~IScene() {
    LOG("Scene object destructed!");
}