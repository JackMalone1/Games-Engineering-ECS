#pragma once

#include <vector>
#include "Component.h"
#include "EntityGlobals.h"
#include <string>

class Entity
{
public:
    void addComponent(Component* component);
    void removeComponent(Component* component);
    std::vector<Component*> getComponents();
    Component* getComponent(std::string tag);

    bool operator==(const Entity& other)
    {
        return m_id == other.m_id;
    }

    Entity()
    {
        m_id = currentEntityCount++;
    }
private:
    std::vector<Component*> m_components;
    uint64_t m_id;
};

