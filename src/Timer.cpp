#include "../include/Timer.h"

Timer::Timer()
{
    reset();
}

void Timer::start()
{
    m_ticks = SDL_GetTicks();
}

void Timer::reset()
{
    m_ticks = 0;
    start();
}

uint32_t Timer::getTicks()
{
    return SDL_GetTicks() - m_ticks;
}

float Timer::getTicksAsSeconds()
{
    return getTicks() / 1000.0f;
}