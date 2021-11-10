#pragma once
#include "Entity.h"
#include "Component.h"
#include "Signature.h"
#include <queue>
#include <array>
class EntityManager
{
public:
    EntityManager()
    {
        for(Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            entities.push(entity);
        }
    }

    Entity addEntity()
    {
        if(numberOfEntities >= MAX_ENTITIES) throw std::exception();

        Entity entity = entities.front();
        entities.pop();
        ++numberOfEntities;
        return entity;
    }

    void removeEntity(Entity entity)
    {
        if(entity >= MAX_ENTITIES) throw std::exception();

        signatures.at(entity).reset();
        entities.push(entity);
        --numberOfEntities;
    }

    void setSignature(Entity entity, Signature signature)
    {
        if(entity >= MAX_ENTITIES) throw std::exception();

        signatures.at(entity) = signature;
    }

    Signature getSignature(Entity entity)
    {
        if(entity >= MAX_ENTITIES) throw std::exception();
        return signatures[entity];
    }
private:
    std::queue<Entity> entities{};
    std::array<Signature, MAX_ENTITIES> signatures{};
    uint32_t numberOfEntities{};
};