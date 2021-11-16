#pragma once
#include <stdint.h>
#include <SDL2/SDL.h>

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

struct HealthComponent
{
    int health;
    std::string entityTag;
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
    SDL_Color colour;
};

struct AIComponent
{
    float xVelocity = 0, yVelocity = 0;
    AIComponent()
    {
        xVelocity = ((float) rand()) / (float) RAND_MAX;
        xVelocity *= (0.1 -(-0.1)) + (-0.1);
        yVelocity = ((float) rand()) / (float) RAND_MAX;
        yVelocity *= (0.1 -(-0.1)) + (-0.1);
    }
};