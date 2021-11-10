#pragma once
#include <algorithm>
#include <vector>
#include "Entity.h"
#include "Coordinator.h"
#include "Component.h"
#include <set>

extern Coordinator m_Coordinator;
class System
{
public:
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
        for(auto& entity : entities)
        {
            RenderComponent& renderComponent = m_Coordinator.GetComponent<RenderComponent>(entity);
            PositionComponent& positionComponent = m_Coordinator.GetComponent<PositionComponent>(entity);
            renderComponent.rectangle.x = positionComponent.x;
            renderComponent.rectangle.y = positionComponent.y;
            SDL_RenderDrawRect(renderer, &renderComponent.rectangle);
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