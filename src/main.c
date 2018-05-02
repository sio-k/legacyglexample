/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#define SDL_MAIN_HANDLED
#include "std.h"

#include "opengl.h"

// convention: module names are CapitalizedCase
// structs are Snake_Case
// functions are camelCase
// constructors are the same name as the struct they construct, but camelCase
// destructors end in Destroy
// constructors/destructors return 0 on failure, non-zero value on success
// local variables are snake_case
// global variables are snake_case and start with g_
// struct members are snake_case
// functions return 0 on error and any non-zero value on success
#include "Input.h"
#include "Window.h"
#include "Render.h"

#include "globals.h"
DEFINE_ALL_GLOBALS

#include "KeyBinds.h"

void gameLoop();
int gameLoopStep();

int main( int argc, char** argv, char** envv )
{
    SDL_SetMainReady();

    // NOTE: BSDs and likely some Linuxes do not support haptic feedback AT ALL.
    // Note also that game controller/joystick support, while common, is not
    // a given. Only initialize these systems if we require them, and fail
    // noisily if we cannot initialize them.
    const int sdl_flags = SDL_INIT_TIMER
                          | SDL_INIT_AUDIO
                          | SDL_INIT_VIDEO
                          | SDL_INIT_EVENTS;

    SDL_Init( sdl_flags );
    if ( SDL_WasInit( 0 ) == ( unsigned ) sdl_flags ) {
        // SDL initialized successfully
    } else {
        perror( "Failed to initialize required SDL subsystems" );
        perror( "Aborting due to failure to initialize a required component" );
        abort();
    }
    atexit( SDL_Quit );

    if ( IMG_Init( IMG_INIT_JPG
                   | IMG_INIT_PNG
                   | IMG_INIT_TIF
                 )
       ) {
        // IMG initialized successfully
    } else {
        perror( "Failed to initialize SDL_image" );
        perror( "Aborting due to failure to initialize a required component" );
        abort();
    }
    atexit( IMG_Quit );

    if ( TTF_Init() == 0 ) {
        // TTF initialized successfully
    } else {
        perror( "Failed to initialize SDL_ttf" );
        perror( "Continuing without support for fonts!" );
    }

    // tell GLEW we want to be able to use "experimental" features
    // GLEW must be initialized after aquiring an OpenGL context ( we don't
    // have one right now )
    // NOTE: Renderer initializes GLEW
    glewExperimental = GL_TRUE;

#if 0
    {
        int tomodify = 0;
        printf( "tomodify == %d\n", tomodify );

        TCCState* s = tcc_new();
        tcc_set_options( s, "-v -bench -Wall -Wunsupported -static" );
        tcc_set_output_type( s, TCC_OUTPUT_MEMORY );
        tcc_compile_string( s,
                            "int main( int argc, char** argv ) { int* tomodify = ( int* ) argv[1]; *tomodify = 55; return 1; }" );
        char** arr = malloc( 2 * sizeof( char* ) );
        arr[0] = "rush_b";
        arr[1] = ( char* ) &tomodify;
        tcc_run( s, 2, arr );
        free( arr );

        tcc_delete( s );

        printf( "tomodify == %d\n", tomodify );
    }
#endif

    INIT_ALL_GLOBALS;

    gameLoop();

    DESTROY_ALL_GLOBALS;

    exit( 0 );
}

Texture2D tex_2d = 0;

void gameLoop()
{
    // register key handlers
    // @{
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_RIGHT,
        keyFnCameraMoveXAdd,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_LEFT,
        keyFnCameraMoveXSubtract,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_UP,
        keyFnCameraMoveYSubtract,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_DOWN,
        keyFnCameraMoveYAdd,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_W,
        keyFnCameraRotateXAdd,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_S,
        keyFnCameraRotateXSubtract,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_Q,
        keyFnCameraRotateYAdd,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_E,
        keyFnCameraRotateYSubtract,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_A,
        keyFnCameraRotateZSubtract,
        g_renderer
    );
    registerKeyHandler(
        g_input,
        SDL_SCANCODE_D,
        keyFnCameraRotateZAdd,
        g_renderer
    );
    // @}

    tex_2d = loadTexture2D( g_renderer, "/home/sioclya/Pictures/68IkRYy.jpg" );

    while ( gameLoopStep() );
}

int gameLoopStep()
{
    SDL_Event ev;
    while ( SDL_PollEvent( &ev ) ) {
        if ( handleEvent( g_input, &ev ) ) {
            // event handled correctly
        } else {
            // clean quit requested or fatal error during event handling
            return 0;
        }
    }

    clear( g_renderer );

    vertex pos = { -0.5f, -0.5f, 0.0f };
    vertex size = { 0.5f, 1.0f, 0.0f };
    color_vec color = { 1.0f, 1.0f, 1.0f, 0.0f };
    draw2DTextureOnRect( g_renderer, tex_2d, pos, size, color );

    present( g_renderer );

    return 1;
}
