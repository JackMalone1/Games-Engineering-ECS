#define SDL_MAIN_HANDLED
#include <iostream>
#include "../include/game.h"
#include <SDL2/SDL.h>
#include <vector>


int main(int argv, char** args)
{


    Game *game = new Game();

    game->run();

    game->cleanup();
    return 0;
}