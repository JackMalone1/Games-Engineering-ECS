#pragma once
#include "System.h"
#include <SDL2/SDL.h>
#include "Coordinator.h"
extern Coordinator coordinator;

class AISystem : public System
{
public:
    
private:
    void processBoundaries(PositionComponent& position)
    {
        if(position.x > 1200)
        {
            position.x = 0;
        }
        else if(position.x < 0)
        {
            position.x = 1200;
        }

        if(position.y > 900)
        {
            position.y = 0;
        }
        else if(position.y < 0)
        {
            position.y = 900;
        }
    }

    bool areColliding(SDL_Rect a, SDL_Rect b)
    {
        return a.x < (b.x + b.w) && (a.x + a.w) > b.x &&
               a.y > (b.y + b.h) && (a.y + a.h) < b.y;
    }
public:
    void move(Entity* targetEntity)
    {
        for(auto& entity : entities)
        {
            auto& position = coordinator.getComponent<PositionComponent>(entity);
            auto& ai = coordinator.getComponent<AIComponent>(entity);
            auto& render = coordinator.getComponent<RenderComponent>(entity);
            auto& targetRender = coordinator.getComponent<RenderComponent>(*targetEntity);
            auto& health = coordinator.getComponent<HealthComponent>(entity);
            position.x += ai.xVelocity;
            position.y += ai.yVelocity;
            processBoundaries(position);
            if(areColliding(targetRender.rectangle, render.rectangle))
            {
                health.health -= 1;
            }
        }     
    }
};