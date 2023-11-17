#include "mainscene.h"
#ifdef DEBUG
#include <iostream>
#endif

MainScene::MainScene(
    SDL_Renderer* renderer_ptr,
    SceneManager* sm,
    ContentManager* cm,
    EventHandler* eh
) : Scene(renderer_ptr, sm, cm, eh) 
{
}

MainScene::~MainScene() {
#ifdef DEBUG
    std::cout << "Deallocating MainScene!" << std::endl << std::endl;
#endif
    for (auto* sprite : sprites) {
        delete sprite;
    }
    sprites.clear();
}

void MainScene::on_load() {
    Scene::on_load();

    SDL_Texture* player_texture = cm->load_texture(renderer_ptr, "assets/player_static.png", "player_texture");
    SDL_Rect source_rect = cm->get_rect("assets/player_static.png");
    SDL_Rect rect = SDL_Rect{0,0,source_rect.w*10, source_rect.h*10};

    rect.x += 200;
    player = new Player(player_texture, rect, source_rect, &sprites);
    rect.x -= 100;
    Sprite* enemy = new Sprite(player_texture, rect, source_rect);

    sprites.push_back(player);
    sprites.push_back(enemy);

    // load fonts test

    // font = TTF_OpenFont("assets/FiraCodeNerdFontPropo-Medium.ttf", 24);
    font = cm->load_font("assets/FiraCodeNerdFontPropo-Medium.ttf", 24, "fira");

    SDL_Color black{0,0,0,0};

    SDL_Surface* text_surf = TTF_RenderText_Solid(font, "Hello, World!", black);
    SDL_Rect text_srect = SDL_Rect{0,0,text_surf->w, text_surf->h};

    SDL_Texture* text_texture = cm->load_texture(renderer_ptr, text_surf, "text", false);

    SDL_FreeSurface(text_surf);

    Sprite* sprite = new Sprite(text_texture, text_srect, text_srect);

    sprites.push_back(sprite);
}
void MainScene::on_unload() {
    Scene::on_unload();
}

void MainScene::update() {
    Scene::update();

    for (Sprite* sprite : sprites) {
        sprite->update(eh);

        if (sprite != player && intersects(player->rect, sprite->rect)) {
#ifdef DEBUG
            std::cout << "intersecting!!" << std::endl;
#endif
        }
    }
}

void MainScene::draw() {
    Scene::draw();

    for (Sprite* sprite : sprites) {
        sprite->draw(renderer_ptr);
    }
}