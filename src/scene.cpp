#include "scene.h"

#include "debugutils.h"

using namespace se;

IScene::IScene()
{
    LOG("Scene object created!");
}

IScene::~IScene() {
    LOG("Scene object destructed!");
}