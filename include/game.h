#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include <map>
#include "System.h"
#include <vector>
#include "Coordinator.h"
class Game
{
public:
    Game();
    bool isRunning();
    void handleEvents();
    void update();
    void render();
    void run();
    void cleanup();
private:
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 900;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* m_font = nullptr;
    SDL_Event e;
    std::vector<Entity> entities{1};
    std::shared_ptr<RenderSystem> renderSystem;
    bool running = true;
};