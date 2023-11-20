# How to Use

First, follow the [installation](../README.md#install) and [compilation](../README.md#compiling-your-program) instructions. If all goes well:

main.cpp:
```cpp
#include <app.h>

int main(int argc, char* argv[]) {
    return 0;
}
```

This program should compile.

Now lets make a game with it!

## 1. Create your App

Override `IApp`.

```cpp
#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "app.h"

class GameApp : public se::IApp {
public:
    GameApp() : IApp() {}
protected:
    void on_load() override;
    void on_unload() override;
    void on_update() override;
    void on_draw() override;
};

#endif
```

Impliment abstract methods:

```cpp
#include "gameapp.h"

void GameApp::on_load() {

}

void GameApp::on_unload() {

}

void GameApp::on_update() {

}

void GameApp::on_draw() {

}
```

You should now be able to run the program and see a window!. (event polling and close-requested events are handled automatically).

## 1. Create your first scene

Override `IScene`

```cpp
#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "scene.h"
#include "sprite.h"
#include "player.h"
#include "utils.h"
#include <vector>

class MainScene : public se::IScene {
public:
    MainScene(
        se::IApp* app
    );
    ~MainScene() override;
    void on_load() override;
    void on_unload() override;
    void on_update() override;
    void on_draw() override;
    void on_scene_enter() override;
    void on_scene_exit() override;
private:
    std::vector<se::Sprite*> sprites;

    // managers
    se::managers::SceneManager* scene_manager;
    se::managers::ContentManager* content_manager;
    se::managers::EventHandler* event_handler;
    se::managers::MusicPlayer* music_player;
    SDL_Renderer* renderer_ptr;
};

#endif
```

Impliment the abstract methods:

```cpp
void MainScene::on_load() {}
void MainScene::on_unload() {}
void MainScene::update() {}
void MainScene::draw() {}
void on_scene_enter() {}
void on_scene_exit() {}
MainScene::~MainScene() {}
```

Use scene in your new app:

example:
```cpp
void GameApp::on_load() {
    scene_manager.add_scene(0, new MainScene(this));
    scene_manager.set_scene(0);
}

void GameApp::on_update() {
    scene_manager.get_scene()->update();
}
```

## 3. Add some stuff!

I recommend clearing the screen with:

```cpp
SDL_SetRenderDrawColor(renderer_ptr, 0,0,0);
SDL_RenderClear(renderer_ptr);

// scene drawing happens here

SDL_RenderPresent(renderer_ptr);
```
Load a texture!

```cpp
content_manager->load_texture("filename.png", "alias");
```
Create a Sprite!
```cpp
se::Sprite sprite(
    content_manager.get_texture("alias"),
    SDL_Rect{0,0,100,200},
    SDL_Rect{0,0,8,16}
    );
```
Use your sprite!
```cpp
sprite.draw(renderer_ptr);
```