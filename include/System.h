#pragma once
#include <algorithm>
#include <vector>
#include "Entity.h"
#include "Component.h"
#include <set>

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