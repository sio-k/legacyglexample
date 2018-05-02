/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "Texture.h"

SDL_Surface* loadIntoGLFriendlyFormat( const char* const path )
{
    if ( path == NULL ) {
        printf( "loadIntoGLFriendlyFormat(): path is NULL!\n" );
        return NULL;
    }

    SDL_Surface* surface = IMG_Load( path );
    if ( surface == NULL ) {
        printf( "Could not load file: %s", IMG_GetError() );
        return NULL;
    }
    SDL_Surface* gl_friendly = SDL_ConvertSurfaceFormat( surface,
                               SDL_PIXELFORMAT_RGBA32, 0 );
    SDL_FreeSurface( surface );

    return gl_friendly;
}
