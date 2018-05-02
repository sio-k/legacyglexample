#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "std.h"
#include "opengl.h"

typedef GLuint Texture2D;

SDL_Surface* loadIntoGLFriendlyFormat( const char* const path );
