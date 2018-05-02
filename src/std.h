#pragma once
/*
 * Copyright (C) Sio Kreuzer. All Rights Reserved.
 */

// paths relative to /usr/include because IDE should not touch CMakeLists.txt
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <tgmath.h>

// we compile in support for TCC (the tiny C compiler) to enable use of an eval function
#include <libtcc.h>

// compile and run str
#define eval( str ) {                                \
        TCCState* state = tcc_new();                     \
        \
        puts( "created tcc state" ); \
        tcc_set_options( state, "-w -static");           \
        puts( "set tcc options" ); \
        tcc_set_output_type( state, TCC_OUTPUT_MEMORY ); \
        puts( "set tcc output type" ); \
        tcc_compile_string( state, str );                \
        puts( "told tcc to compile str" ); \
        if ( tcc_run( state, 1, "rush_b" ) == -1 ) { \
            puts( "tcc_run error!" ); \
        }                   \
        puts( "told tcc to run" ); \
        \
        tcc_delete( state );                             \
        puts( "destroyed tcc state" ); \
    }

// compile and run file located at path
#define eval_file( path ) {                          \
        TCCState* state = tcc_new();                     \
        \
        tcc_set_options( state, "-w -static" );          \
        tcc_set_output_type( state, TCC_OUTPUT_MEMORY ); \
        tcc_add_file( state, path );                     \
        tcc_run( state, 1, "rush_b" );                   \
        \
        tcc_delete( state );                             \
    }

/*
 * BASIC TYPES
 */

// signed types
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// unsigned types
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// we use regular size_t

typedef GLfloat  f32;
typedef GLdouble f64;
