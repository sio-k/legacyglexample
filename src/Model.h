#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "std.h"

#include "opengl.h"

#include "vector.h"

#include "Texture.h"

typedef vec3 vertex;
enum
{
    VERTEX_X    = 0,
    VERTEX_Y    = 1,
    VERTEX_Z    = 2,
    VERTEX_SIZE = 3
};

typedef vertex triangle[3];
enum
{
    TRI_VERT_A     = 0,
    TRI_VERT_B     = 1,
    TRI_VERT_C     = 2,
    TRI_VERT_COUNT = 3,
    TRI_SIZE       = 3
};

typedef struct Model
{
    size_t tri_count;
    triangle* tris; // array of tris
    GLuint vbo_num; // save the vbo this model was uploaded to here (otherwise leave as 0)
} Model;

// no custom allocator yet, but separate "build" function to perform placement new
// constructs new model on heap
Model* model( size_t num_tris );

// attempts no free on possibly allocated tri array in model!
void modelBuild( Model* to_init, size_t num_tris );

// frees tris in model
void modelFreeTris( Model* to_free_tris_of );

// destroys model on heap
void modelDestroy( Model* to_destroy );
