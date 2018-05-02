#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

/*
 * Engine globals. All of 'em.
 *
 * Initialized in main.c.
 * Assigned in the body of main().
 * Destroyed at the end of main().
 */

#include "std.h"

#include "Render.h"
#include "Window.h"
#include "Input.h"

extern Input*      g_input;
extern Window*     g_window;
extern Renderer*   g_renderer;
extern Game_State* g_game_state;
extern struct Static_Game_Object_Textures g_static_game_object_textures;

// TODO: replace with actual textures
#define BULLET_TEXTURE_PATH      NULL
#define TANK_BASE_TEXTURE_PATH   NULL
#define TANK_TURRET_TEXTURE_PATH NULL

#define DEFINE_ALL_GLOBALS                  \
    extern Input*      g_input = NULL;      \
    extern Window*     g_window = NULL;     \
    extern Renderer*   g_renderer = NULL;   \
    extern Game_State* g_game_state = NULL;


#define INIT_ALL_GLOBALS \
    g_window = window( \
                       "Memeviewer 9000", \
                       640, \
                       480, \
                       SDL_WINDOW_RESIZABLE \
                       | SDL_WINDOW_SHOWN \
                       | SDL_WINDOW_OPENGL \
                     ); \
    assert( g_window != NULL ); \
    \
    g_renderer = renderer( g_window ); \
    assert( g_renderer != NULL ); \
    \
    g_game_state = NULL; \
    g_input = input( g_game_state, g_renderer ); \
    assert( g_input != NULL ); \
    \
    fillWithDefaultControls( g_input );

#define DESTROY_ALL_GLOBALS \
    rendererDestroy( g_renderer ); \
    inputDestroy( g_input ); \
    windowDestroy( g_window );
