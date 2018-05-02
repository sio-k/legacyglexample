#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "std.h"

typedef struct Window
{
    SDL_Window* win;
} Window;

Window* window(
    const char* const title,
    const i32 width,
    const i32 height,
    const int flags
);
void windowDestroy( Window* win );
