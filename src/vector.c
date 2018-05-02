/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "vector.h"

void vec2Add( const vec2 a_in, const vec2 b_in, vec2 out )
{
    out[VEC2_X] = a_in[VEC2_X] + b_in[VEC2_X];
    out[VEC2_Y] = a_in[VEC2_Y] + b_in[VEC2_Y];
}

void vec2ScalarMultiply( const vec2 a_in, const f64 scalar, vec2 out )
{
    out[VEC2_X] = a_in[VEC2_X] * scalar;
    out[VEC2_Y] = a_in[VEC2_Y] * scalar;
}

int vec2IsNull( const vec2 a_in )
{
    return ( a_in[VEC2_X] == 0.0f ) && ( a_in[VEC2_Y] == 0.0f );
}

void vec3Add( const vec3 a_in, const vec3 b_in, vec3 out )
{
    out[VEC3_X] = a_in[VEC3_X] + b_in[VEC3_X];
    out[VEC3_Y] = a_in[VEC3_Y] + b_in[VEC3_Y];
    out[VEC3_Z] = a_in[VEC3_Z] + b_in[VEC3_Z];
}

void vec3ScalarMultiply( const vec3 a_in, const f64 scalar, vec3 out )
{
    out[VEC3_X] = a_in[VEC3_X] * scalar;
    out[VEC3_Y] = a_in[VEC3_Y] * scalar;
    out[VEC3_Z] = a_in[VEC3_Z] * scalar;
}

int vec3IsNull( const vec3 a_in )
{
    return ( a_in[VEC3_X] == 0.0f ) && ( a_in[VEC3_Y] == 0.0f )
           && ( a_in[VEC3_Z] == 0.0f );
}
