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
public:
    void move()
    {
        for(auto& entity : entities)
        {
            auto& position = coordinator.getComponent<PositionComponent>(entity);
            auto& ai = coordinator.getComponent<AIComponent>(entity);
            position.x += ai.xVelocity;
            position.y += ai.yVelocity;
            processBoundaries(position);
        }     
    }

    AISystem()
    {
        
    }
};