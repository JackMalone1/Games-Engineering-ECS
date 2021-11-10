#pragma once

#include "System.h"
#include "Signature.h"
#include "Entity.h"
#include "Component.h"
#include <memory>
#include <unordered_map>

class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
        const char* typeName = typeid(T).name();
        //if(systems.find(typeName) != systems.end()) throw "Trying to add the same system more than once\n";

        std::shared_ptr<T> system = std::make_shared<T>();
        systems.insert({typeName, system});
        return system;
    }

    template<typename T>
    void setSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();
        //if(systems.find(typeName) == systems.end()) throw "Trying to use system before registering it.\n";
        signatures.insert({typeName, signature});
    }

    void entityDestroyed(Entity entity)
    {
        for (auto const& pair : systems)
        {
            auto const& system = pair.second;

            system->entities.erase(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for (auto const& pair : systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];

            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->entities.insert(entity);
            }
            else
            {
                system->entities.erase(entity);
            }
        }
    }
private:
    std::unordered_map<const char*, Signature> signatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};