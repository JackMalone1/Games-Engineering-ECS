#pragma once


#include <vector>


class Factory
{
public:
    template<typename T>
    T* getObject(){return new T();}
};