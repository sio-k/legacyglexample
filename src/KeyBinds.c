/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "KeyBinds.h"

int keyFnCameraRotateXAdd( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_rot[VERTEX_X] += 0.3f;
    return 1;
}

int keyFnCameraRotateXSubtract( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_rot[VERTEX_X] -= 0.3f;
    return 1;
}

int keyFnCameraRotateYAdd( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_rot[VERTEX_Y] += 0.3f;
    return 1;
}

int keyFnCameraRotateYSubtract( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_rot[VERTEX_Y] -= 0.3f;
    return 1;
}

int keyFnCameraRotateZAdd( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_rot[VERTEX_Z] += 0.3f;
    return 1;
}

int keyFnCameraRotateZSubtract( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_rot[VERTEX_Z] -= 0.3f;
    return 1;
}

int keyFnCameraMoveXAdd( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_pos[VERTEX_X] += 0.3f;
    return 1;
}

int keyFnCameraMoveXSubtract( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_pos[VERTEX_X] -= 0.3f;
    return 1;
}

int keyFnCameraMoveYAdd( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_pos[VERTEX_Y] += 0.3f;
    return 1;
}

int keyFnCameraMoveYSubtract( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_pos[VERTEX_Y] -= 0.3f;
    return 1;
}

int keyFnCameraMoveZAdd( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_pos[VERTEX_Z] += 0.3f;
    return 1;
}

int keyFnCameraMoveZSubtract( void* ren )
{
    Renderer* r = ( Renderer* ) ren;
    r -> camera_pos[VERTEX_Z] -= 0.3f;
    return 1;
}

int keyFnQuit( void* unused )
{
    return 0;
}
