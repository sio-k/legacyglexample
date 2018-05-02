/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "Window.h"

Window* window( const char* const title
                , const i32 width
                , const i32 height
                , const int
                flags // int because platform-specific and an enum is always the size of an int
              )
{
    Window* win = malloc( sizeof( Window ) );
    win -> win = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, width, height, flags );
    assert( win -> win != NULL );
    return win;
}

void windowDestroy( Window* win )
{
    SDL_DestroyWindow( win -> win );
    free( win );
}
