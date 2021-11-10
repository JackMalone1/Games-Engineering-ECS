#pragma once
#include <algorithm>
#include <vector>
#include "Entity.h"
#include "Component.h"
#include <set>
#include "Coordinator.h"
extern Coordinator coordinator;
class System
{
public:
    System() = default;
    std::set<Entity> entities;
};


class ControlSystem : public System
{
private:

public:

};

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
        }
    }
};

class AISystem : public System
{
private:

public:

};

class HealthSystem : public System
{
private:

public:

};