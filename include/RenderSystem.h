#pragma once
#include "System.h"
#include <SDL2/SDL.h>
#include "Coordinator.h"
extern Coordinator coordinator;

class RenderSystem : public System
{
private:

public:
    void render(SDL_Renderer* renderer)
    {
        for(auto const& entity : entities)
        {
            auto& position = coordinator.getComponent<PositionComponent>(entity);
            auto& renderable = coordinator.getComponent<RenderComponent>(entity);
            renderable.rectangle.x = position.x;
            renderable.rectangle.y = position.y;
            SDL_SetRenderDrawColor(renderer, renderable.colour.r,renderable.colour.g,renderable.colour.b,renderable.colour.a);
            SDL_RenderFillRect(renderer, &renderable.rectangle);
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        }
    }
};
