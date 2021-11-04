#pragma once
#include <SDL2/SDL.h>
class Timer{
public:
    Timer();
    void start();
    void reset();
    uint32_t getTicks();
    float getTicksAsSeconds();
private:
    uint32_t m_ticks;    
};