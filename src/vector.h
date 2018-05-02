#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "std.h"

/*
 * Simple library to support vector math.
 */

typedef f64 vec2[2];
enum
{
    VEC2_X = 0,
    VEC2_Y = 1,
    VEC2_SIZE = 2
};

void vec2Add( const vec2 a_in, const vec2 b_in, vec2 out );
void vec2ScalarMultiply( const vec2 a_in, const f64 scalar, vec2 out );
int vec2IsNull( const vec2 a_in );

typedef f64 vec3[3];
enum
{
    VEC3_X = 0,
    VEC3_Y = 1,
    VEC3_Z = 2,
    VEC3_ROTATION = 2,
    VEC3_SIZE = 3
};

void vec3Add( const vec3 a_in, const vec3 b_in, vec3 out );
void vec3ScalarMultiply( const vec3 a_in, const f64 scalar, vec3 out );
int vec3IsNull( const vec3 a_in );
