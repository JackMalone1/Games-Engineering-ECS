#pragma once
#include <stdint.h>
#include <SDL2/SDL.h>
using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

struct HealthComponent
{
    int health;
};

struct PositionComponent
{
    float x, y;
};

struct InputComponent
{
    SDL_Event event;
};

struct RenderComponent
{
    SDL_Rect rectangle;
    float w,h;
};