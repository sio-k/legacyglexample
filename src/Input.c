/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "Input.h"

#include "KeyBinds.h"

Input* input( Game_State* gst, Renderer* ren )
{
    Input* self = calloc( 1, sizeof( Input ) );
    self -> gst = gst;
    self -> ren = ren;
    return self;
}

void inputDestroy( Input* input_map )
{
    free( input_map );
}

void registerKeyHandler(
    Input* const input_map,
    const SDL_Scancode key,
    key_function const fn,
    void* const fn_context
)
{
    input_map -> key_handler_map[key].fn = fn;
    input_map -> key_handler_map[key].fn_context = fn_context;
}

int handleEvent( Input* const input_map, const SDL_Event* const ev )
{
    switch ( ev -> type ) {
        case SDL_QUIT:
            return 0;
            break;
        case SDL_KEYDOWN:
            return handleKeypress( input_map, ev -> key.keysym.scancode );
            break;
        case SDL_KEYUP:
            // ignored
            break;
        case SDL_MOUSEMOTION:
            // ignored
            break;
        case SDL_MOUSEBUTTONDOWN:
            return handleMouseButton( input_map, ev );
            break;
        case SDL_MOUSEBUTTONUP:
            // ignored for now
            break;
        default:
            // ignored
            break;
    }
    return 1;
}

int handleKeypress( Input* const input_map, const SDL_Scancode key )
{
    key_function const fn = input_map -> key_handler_map[key].fn;
    void* const fn_context = input_map -> key_handler_map[key].fn_context;
    if ( fn_context ) {
        return fn( fn_context );
    } else {
        return -1; // non-zero, failed to find handler for key
    }
}

int handleMouseButton( Input* const input_map, const SDL_Event* const ev )
{
    // chasing pointers here. Not a big issue
    f64 ratio = ( f64 ) input_map -> ren -> width
                / ( f64 ) input_map -> ren -> height;
    f64 normalized_x = ( f64 ) ev -> button.x
                       / ( f64 ) input_map -> ren -> width;
    normalized_x = normalized_x * ratio;
    f64 normalized_y = ( f64 ) ev -> button.y
                       / ( f64 ) input_map -> ren -> height;
    // NOTE: doesn't do anything, but does correctly normalize x/y coords to engine coordinate system
    return 0;
}

void fillWithDefaultControls( Input* const input_map )
{
    // quit on ESC
    input_map -> key_handler_map[SDL_SCANCODE_ESCAPE].fn = keyFnQuit;
    input_map -> key_handler_map[SDL_SCANCODE_ESCAPE].fn_context = input_map;
}
