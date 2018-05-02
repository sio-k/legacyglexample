#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "std.h"

#include "Render.h"

#define Game_State void

typedef int ( *key_function )( void* );

typedef struct Key_Handler
{
    key_function fn;
    void*        fn_context;
} Key_Handler;

typedef struct Input
{
    Game_State* gst;
    Renderer* ren;
    Key_Handler key_handler_map[SDL_NUM_SCANCODES];
} Input;

Input* input( Game_State* gst, Renderer* ren );
void inputDestroy( Input* input_map );

// overwrites previous handler for this key if one exists already in the map
// NOTE: if fn_context is equal to nullptr, fn will not be called.
void registerKeyHandler(
    Input* const input_map,
    const SDL_Scancode key,
    key_function const fn,
    void* const fn_context
);

int handleEvent( Input* const input_map, const SDL_Event* const ev );
int handleKeypress( Input* const input_map, const SDL_Scancode key );
int handleMouseButton( Input* const input_map, const SDL_Event* const ev );

void fillWithDefaultControls( Input* input_map );
