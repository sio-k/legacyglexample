/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "opengl.h"

void initializeGLEW()
{
    static i8 glewInitialized; // boolean
    if ( glewInitialized ) {
        return;
    }

    GLenum glewInitError = glewInit();
    if ( glewInitError != GLEW_OK ) {
        printf( "Error while initializing GLEW: %s\n",
                glewGetErrorString( glewInitError ) );
        glewInitialized = 0;
    } else {
        glewInitialized = 1;
    }
}

#define GL_VERSION_CHECK( x )                 \
    if ( x ) {                                \
        printf( #x );                         \
        printf( " supported by library.\n" ); \
    }
#define GLEW_VERSION_CHECK( x )                 \
    if ( x ) {                                  \
        printf( #x );                           \
        printf( " supported by loaded shared object.\n" ); \
    }

void glVersionCheck()
{
    // check versions supported by library
    GL_VERSION_CHECK( GL_VERSION_1_1 );
    GL_VERSION_CHECK( GL_VERSION_1_2 );
    GL_VERSION_CHECK( GL_VERSION_1_3 );
    GL_VERSION_CHECK( GL_VERSION_1_4 );
    GL_VERSION_CHECK( GL_VERSION_1_5 );

    GL_VERSION_CHECK( GL_VERSION_2_0 );
    GL_VERSION_CHECK( GL_VERSION_2_1 );

    GL_VERSION_CHECK( GL_VERSION_3_0 );
    GL_VERSION_CHECK( GL_VERSION_3_1 );
    GL_VERSION_CHECK( GL_VERSION_3_2 );
    GL_VERSION_CHECK( GL_VERSION_3_3 );

    GL_VERSION_CHECK( GL_VERSION_4_0 );
    GL_VERSION_CHECK( GL_VERSION_4_1 );
    GL_VERSION_CHECK( GL_VERSION_4_2 );
    GL_VERSION_CHECK( GL_VERSION_4_3 );
    GL_VERSION_CHECK( GL_VERSION_4_4 );

    GLEW_VERSION_CHECK( GLEW_VERSION_1_1 );
    GLEW_VERSION_CHECK( GLEW_VERSION_1_2 );
    GLEW_VERSION_CHECK( GLEW_VERSION_1_3 );
    GLEW_VERSION_CHECK( GLEW_VERSION_1_4 );
    GLEW_VERSION_CHECK( GLEW_VERSION_1_5 );

    GLEW_VERSION_CHECK( GLEW_VERSION_2_0 );
    GLEW_VERSION_CHECK( GLEW_VERSION_2_1 );

    GLEW_VERSION_CHECK( GLEW_VERSION_3_0 );
    GLEW_VERSION_CHECK( GLEW_VERSION_3_1 );
    GLEW_VERSION_CHECK( GLEW_VERSION_3_2 );
    GLEW_VERSION_CHECK( GLEW_VERSION_3_3 );

    GLEW_VERSION_CHECK( GLEW_VERSION_4_0 );
    GLEW_VERSION_CHECK( GLEW_VERSION_4_1 );
    GLEW_VERSION_CHECK( GLEW_VERSION_4_2 );
    GLEW_VERSION_CHECK( GLEW_VERSION_4_3 );
    GLEW_VERSION_CHECK( GLEW_VERSION_4_4 );
}

#undef GL_VERSION_CHECK
#undef GLEW_VERSION_CHECK

void glFeatureCheck()
{
    if ( GLEW_ARB_vertex_buffer_object ) {
        puts( "VBOs supported" );
    } else {
        puts( "VBOs not supported" );
    }
}
