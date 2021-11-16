#pragma once
#include "System.h"
#include <SDL2/SDL.h>
#include "Coordinator.h"
extern Coordinator coordinator;
#include <iostream>
class HealthSystem : public System
{
private:

public:
    void displayHealth()
    {
        for(auto& entity : entities)
        {
            auto& health = coordinator.getComponent<HealthComponent>(entity);
            std::cout << "Entity: " << health.entityTag << " has " << health.health << " health.\n";
        }      
    }
};