#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "std.h"
#include "opengl.h"

#include "Window.h"

#include "Model.h"
#include "Texture.h"

typedef f64 color_vec[4];
enum
{
    COLOR_VEC_R = 0,
    COLOR_VEC_G = 1,
    COLOR_VEC_B = 2,
    COLOR_VEC_A = 3,
    COLOR_VEC_SIZE = 4
};

// NULL-terminated singly linked list of loaded textures
typedef struct Texture2D_List_Item
{
    Texture2D tex;
    struct Texture2D_List_Item* next;
} Texture2D_List_Item;

Texture2D_List_Item* texture2DListItem( Texture2D tex );
void texture2DListItemDestroy( Texture2D_List_Item* to_destroy );

// returns to_prepend
Texture2D_List_Item* texture2DListPrepend(
    Texture2D_List_Item* to_prepend_to,
    Texture2D_List_Item* to_prepend
);
void texture2DListAppend(
    Texture2D_List_Item* to_append_to,
    Texture2D_List_Item* to_append
);

typedef struct Renderer
{
    SDL_GLContext context;
    Window* win;

    i32 width;
    i32 height;

    vertex camera_pos;
    vertex camera_rot;

    Texture2D_List_Item* loaded_2d_textures;
} Renderer;

Renderer* renderer( Window* win );
void rendererDestroy( Renderer* to_destroy );

// clears the screen and readjusts the size of the viewport if necessary
void clear( Renderer* ren );

void draw2DTextureOnRect(
    Renderer* ren,
    const Texture2D tex,
    const vertex pos,
    const vertex size,
    const color_vec color // { 1.0f, 1.0f, 1.0f, 0.0f } for no coloring
);

void draw2DTextureOnRectWithRotation(
    Renderer* ren,
    const Texture2D tex,
    const vec2 pos,
    const vec2 size,
    const f64 rotation,
    const color_vec color
);

// draw to screen through the arrays from index 0 to amount
void draw2DTextureLayer( Renderer* ren,
                         const Texture2D* textures,
                         const vertex* positions_with_z_rotation,
                         const vertex* sizes,
                         const color_vec* colors,
                         const size_t amount
                       );
void draw3DModel(
    Renderer* ren,
    Model* to_draw,
    vertex translate_to
);

void present( Renderer* ren );

Texture2D loadTexture2D( Renderer* ren, const char* const path );
