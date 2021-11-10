#pragma once

#include "ComponentArray.h"
#include "Component.h"
#include "Entity.h"
#include "Signature.h"
#include <any>
#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
    template<typename T> 
    void registerComponent()
    {
        const char* typeName = typeid(T).name();
        componentTypes.insert({typeName, nextComponentType});
        componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        ++nextComponentType;
    }

    template<typename T>
    ComponentType getComponentType()
    {
        const char* typeName = typeid(T).name();
        if(componentTypes.find(typeName) == componentTypes.end()) throw "cannot find component type \n";
        return componentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        getComponentArray<T>()->addComponent(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        getComponentArray<T>()->removeComponent(entity);
    }

    template<typename T>
    T& getComponent(Entity entity)
    {
        return getComponentArray<T>()->getComponent(entity);
    }

    void entityDestroyed(Entity entity)
    {
        for(auto const& pair : componentArrays)
        {
            auto const& component = pair.second;

            component->entityDestroyed(entity);
        }
    }
private:
    std::unordered_map<const char*, ComponentType> componentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};
    ComponentType nextComponentType{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        const char* typeName = typeid(T).name();
        if(componentTypes.find(typeName) == componentTypes.end()) throw "cannot find component type \n";

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};