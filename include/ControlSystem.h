#pragma once
#include "System.h"
#include <SDL2/SDL.h>
#include "Coordinator.h"
extern Coordinator coordinator;

class ControlSystem : public System
{
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
    void processEvents(SDL_Event& event)
    {
        for(auto& entity : entities)
        {
            auto& position = coordinator.getComponent<PositionComponent>(entity);
            auto& input = coordinator.getComponent<InputComponent>(entity);

            input.event = event;

            if(input.event.type == SDL_KEYDOWN)
            {
                if(input.event.key.keysym.sym == SDLK_d)
                {
                    position.x += 3;
                }
                if(input.event.key.keysym.sym == SDLK_w)
                {
                    position.y -= 3;
                }
                if(input.event.key.keysym.sym == SDLK_a)
                {
                    position.x -= 3;
                }
                if(input.event.key.keysym.sym == SDLK_s)
                {
                    position.y += 3;
                }
            }

            processBoundaries(position);
        }      
    }
};