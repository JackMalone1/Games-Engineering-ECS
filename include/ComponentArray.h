#pragma once
#include "Entity.h"
#include "Component.h"
#include "Signature.h"
#include <array>
#include <unordered_map>

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void addComponent(Entity entity, T component)
    {
        if(entityToIndex.find(entity) != entityToIndex.end()) throw "component is on entity already";

        size_t index = size;
        entityToIndex.at(entity) = index;
        indexToEntity.at(index) = entity;
        componentArray.at(index) = component;
        size++;
    }

    void removeComponent(Entity entity)
    {
        if(entityToIndex.find(entity) == entityToIndex.end()) throw "Trying to remove component that doesnt exist";

        size_t indexOfRemovedEntity = entityToIndex[entity];
		size_t indexOfLastElement = size - 1;
		componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = indexToEntity[indexOfLastElement];
		entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntity[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndex.erase(entity);
		indexToEntity.erase(indexOfLastElement);

		size--;
    }

    T& getComponent(Entity entity)
    {
        if(entityToIndex.find(entity) == entityToIndex.end()) throw "Trying to remove component that doesnt exist";

        return componentArray.at(entityToIndex[entity]);
    }

    void entityDestroyed(Entity entity) override
    {
        if(entityToIndex.find(entity) != entityToIndex.end())
        {
            removeComponent(entity);
        }
    }
private:
    std::array<T, MAX_ENTITIES> componentArray{};
    std::unordered_map<Entity, size_t> entityToIndex{};
    std::unordered_map<size_t, Entity> indexToEntity{};
    size_t size{};
};