#pragma once
#include <algorithm>
#include <vector>
#include "Entity.h"

class System
{
private:
    std::vector<Entity> m_entities;
public:
    void addEntity(Entity entity)
    {
        m_entities.push_back(entity);
    }
    void update();
    void removeEntity(Entity entity)
    {
        std::vector<Entity>::iterator it = m_entities.begin();
        std::vector<Entity>::iterator end = m_entities.end();
        for(; it != end; it++)
        {
            if(*it == entity)
            {
                m_entities.erase(it);
                return;
            }
        }
    }
    std::vector<Entity> getEntities();
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