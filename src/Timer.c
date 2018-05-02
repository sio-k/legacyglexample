/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "Timer.h"

static u64 timer_res;
static u64 timer_factor; // factor to multiply with to get to microseconds

void timer()
{
    timer_res = SDL_GetPerformanceFrequency();
    if ( timer_res < 1000000 ) {
        // resolution worse than microseconds
        perror( "Timer resolution worse than 1/1 000 000th of a second!" );
        abort();
    }

    // calculate factor
    timer_factor = timer_res / 1000000;
}

u64 timer_resolution()
{
    return timer_res;
}

u64 ticks()
{
    return SDL_GetPerformanceCounter();
}

f64 time()
{
    return ( f64 ) SDL_GetPerformanceCounter() * ( f64 ) timer_res;
}
