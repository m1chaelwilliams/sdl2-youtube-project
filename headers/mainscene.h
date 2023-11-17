#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "scene.h"
#include "sprite.h"
#include "player.h"
#include "utils.h"
#include <SDL2/SDL_ttf.h>
#include <vector>

class MainScene : public Scene {
public:
    MainScene(
        SDL_Renderer* renderer_ptr,
        SceneManager* sm,
        ContentManager* cm,
        EventHandler* eh
    );
    ~MainScene() override;
    void on_load() override;
    void on_unload() override;
    void update() override;
    void draw() override;
private:
    std::vector<Sprite*> sprites;
    TTF_Font* font;

    // temp
    Player* player;
};

#endif