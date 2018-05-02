#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

// File for all functions bound to keys

#include "Input.h"
#include "Render.h"

// camera-related
// @{
int keyFnCameraRotateXAdd( void* ren );
int keyFnCameraRotateXSubtract( void* ren );

int keyFnCameraRotateYAdd( void* ren );
int keyFnCameraRotateYSubtract( void* ren );

int keyFnCameraRotateZAdd( void* ren );
int keyFnCameraRotateZSubtract( void* ren );

int keyFnCameraMoveXAdd( void* ren );
int keyFnCameraMoveXSubtract( void* ren );

int keyFnCameraMoveYAdd( void* ren );
int keyFnCameraMoveYSubtract( void* ren );

int keyFnCameraMoveZAdd( void* ren );
int keyFnCameraMoveZSubtract( void* ren );
// @}

// quitting function
int keyFnQuit( void* );
