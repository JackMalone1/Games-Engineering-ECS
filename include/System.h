#pragma once
#include "Entity.h"
#include <set>
class System
{
public:
    System() = default;
    std::set<Entity> entities;
};
