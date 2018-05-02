/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "Render.h"

void adjustRendererSizeToFitWindow( Renderer* ren );

Renderer* renderer( Window* win )
{
    Renderer* ren = calloc( 1, sizeof( Renderer ) );

    ren -> win = win;
    SDL_GL_GetDrawableSize( win -> win, &ren -> width, &ren -> height );

    // GL setup

    // specify attributes and get context
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    ren -> context = SDL_GL_CreateContext( win -> win );
    assert( ren -> context != NULL );

    // we have a context so we can initialize GLEW
    initializeGLEW();

    // check for and print supported versions and features that are interesting to us
    glVersionCheck();
    glFeatureCheck();

    // enable vertical sync
    SDL_GL_SetSwapInterval( 1 );

    // enable 2D textures
    glEnable( GL_TEXTURE_2D );

    // enable z-culling
    glEnable( GL_DEPTH_TEST );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPushMatrix();

    glShadeModel( GL_SMOOTH );

    adjustRendererSizeToFitWindow( ren );

    return ren;
}

void rendererDestroy( Renderer* to_destroy )
{
    for (
        Texture2D_List_Item* li = to_destroy -> loaded_2d_textures;
        li != NULL;
    ) {
        Texture2D_List_Item* next = li -> next;

        glDeleteTextures( 1, &li -> tex );
        texture2DListItemDestroy( li );

        li = next;
    }

    SDL_GL_DeleteContext( to_destroy -> context );

    free( to_destroy );
}

void clear( Renderer* ren )
{
    const i32 old_width = ren -> width;
    const i32 old_height = ren -> height;
    SDL_GL_GetDrawableSize( ren -> win -> win, &ren -> width, &ren -> height );

    if ( old_width != ren -> width || old_height != ren -> height ) {
        adjustRendererSizeToFitWindow( ren );
    }

    // set clear color
    glClearColor( 0.1f // R
                  , 0.1f // G
                  , 0.1f // B
                  , 1.0f // A
                );
    // clear colors and depth buffer
    glClear( GL_COLOR_BUFFER_BIT
             | GL_DEPTH_BUFFER_BIT
           );

    // translate and rotate camera
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
    glLoadIdentity();
    glTranslated(
        ren -> camera_pos[VERTEX_X],
        ren -> camera_pos[VERTEX_Y],
        ren -> camera_pos[VERTEX_Z]
    );
    glRotated( ren -> camera_rot[VERTEX_X], 1.0f, 0.0f, 0.0f );
    glRotated( ren -> camera_rot[VERTEX_Y], 0.0f, 1.0f, 0.0f );
    glRotated( ren -> camera_rot[VERTEX_Z], 0.0f, 0.0f, 1.0f );
    glPushMatrix();
}

void draw2DTextureOnRect(
    Renderer* ren,
    const Texture2D tex,
    const vertex pos,
    const vertex size,
    const color_vec color // { 1.0f, 1.0f, 1.0f, 0.0f } for no coloring
)
{
    glBindTexture( GL_TEXTURE_2D, ( GLuint ) tex );

    glBegin( GL_QUADS );
    {
        glColor4f( color[COLOR_VEC_R], color[COLOR_VEC_G], color[COLOR_VEC_B],
                   color[COLOR_VEC_A] );

        glTexCoord2d( 0.0f, 0.0f );
        glVertex3d(
            pos[VERTEX_X],
            pos[VERTEX_Y],
            0.0f
        );

        glTexCoord2d( 0.0f, 1.0f );
        glVertex3d(
            pos[VERTEX_X],
            pos[VERTEX_Y] + size[VERTEX_Y],
            0.0f
        );

        glTexCoord2d( 1.0f, 1.0f );
        glVertex3d(
            pos[VERTEX_X] + size[VERTEX_X],
            pos[VERTEX_Y] + size[VERTEX_Y],
            0.0f
        );

        glTexCoord2d( 1.0f, 0.0f );
        glVertex3d(
            pos[VERTEX_X] + size[VERTEX_X],
            pos[VERTEX_Y],
            0.0f
        );
    }
    glEnd();

    glBindTexture( GL_TEXTURE_2D, 0 );
}

void draw2DTextureOnRectWithRotation(
    Renderer* ren,
    const Texture2D tex,
    const vec2 pos,
    const vec2 size,
    const f64 rotation,
    const color_vec color
)
{
    glPushMatrix();
    {
        glRotated( rotation, 0.0f, 0.0f, 1.0f );

        glBindTexture( GL_TEXTURE_2D, ( GLuint ) tex );

        glBegin( GL_QUADS );
        {
            glColor4f( color[COLOR_VEC_R],
                       color[COLOR_VEC_G],
                       color[COLOR_VEC_B],
                       color[COLOR_VEC_A]
                     );

            glTexCoord2d( 0.0f, 0.0f );
            glVertex3d(
                pos[VEC2_X],
                pos[VEC2_Y],
                0.0f
            );

            glTexCoord2d( 0.0f, 1.0f );
            glVertex3d(
                pos[VEC2_X],
                pos[VEC2_Y] + size[VEC2_Y],
                0.0f
            );

            glTexCoord2d( 1.0f, 1.0f );
            glVertex3d(
                pos[VEC2_X] + size[VEC2_X],
                pos[VEC2_Y] + size[VEC2_Y],
                0.0f
            );

            glTexCoord2d( 1.0f, 0.0f );
            glVertex3d(
                pos[VEC2_X] + size[VEC2_X],
                pos[VEC2_Y],
                0.0f
            );
        }
        glEnd();

        glBindTexture( GL_TEXTURE_2D, 0 );

    }
    glPopMatrix();
}

// draw to screen starting at index 0 going to index amount
void draw2DTextureLayer( Renderer* ren,
                         const Texture2D* textures,
                         const vertex* positions_with_z_rotation,
                         const vertex* sizes,
                         const color_vec* colors,
                         const size_t amount
                       )
{
    glPushMatrix();
    // TODO: draw a bunch of 2D textures to screen in no particular order
    for ( size_t i = 0; i < amount; i++ ) {
        // swap in previous matrix again, then apply transformation
        glPopMatrix();
        glPushMatrix();

        glRotated( positions_with_z_rotation[i][VERTEX_Z], 0.0f, 0.0f, 1.0f );
        draw2DTextureOnRect( ren, textures[i], positions_with_z_rotation[i], sizes[i],
                             colors[i] );
    }
    glPopMatrix();
}

void draw3DModel( Renderer* ren, Model* to_draw, vertex translate_to )
{
    glPushMatrix();

    glTranslated(
        translate_to[VERTEX_X],
        translate_to[VERTEX_Y],
        translate_to[VERTEX_Z]
    );

    // TODO: rotation

    glColor3f( 0.2f, 0.2f, 0.2f );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( TRI_VERT_COUNT, GL_DOUBLE, 0, to_draw -> tris );

    // TODO: gltexcoordpointer

    glDrawArrays( GL_TRIANGLES, 0, to_draw -> tri_count * TRI_VERT_COUNT );

    glPopMatrix();
}

void present( Renderer* ren )
{
    SDL_GL_SwapWindow( ren -> win -> win );
}

void adjustRendererSizeToFitWindow( Renderer* ren )
{
    // set new viewport width and height
    glViewport( 0, 0, ren -> width, ren -> height );

    // make sure orthographic projection matrix is correct for our new res ratio
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // HOR+ scaling
    const f64 ratio = ( f64 ) ren -> width
                      / ( f64 ) ren -> height
                      / ( f64 ) 2.0f;
    glOrtho(
        -ratio, // left end
        ratio,  // right end
        1.0f,   // bottom end
        -1.0f,  // top end
        1.0f,   // near end
        -1.0f   // far end
    );

    // back to Modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
    glPushMatrix();
}

Texture2D loadTexture2D( Renderer* ren, const char* const path )
{
    assert( ren != NULL );
    // make sure we've been given a valid path
    if ( path == NULL ) {
        printf( "loadTexture2D(): path is NULL!\n" );
        return 0;
    }

    SDL_Surface* surface = loadIntoGLFriendlyFormat( path );
    if ( surface == NULL ) {
        return 0;
    }

    GLuint tex_num = 0;
    GLuint width = ( GLuint ) surface -> w;
    GLuint height = ( GLuint ) surface -> h;

    // generate a texture id and bind it to be a 2D texture
    glGenTextures( 1, &tex_num );
    glBindTexture( GL_TEXTURE_2D, tex_num );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        surface -> pixels
    );

    // set bilinear filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    // set texture to repeat on wraparound
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glBindTexture( GL_TEXTURE_2D, 0 );

    SDL_FreeSurface( surface );

    ren -> loaded_2d_textures = texture2DListPrepend( ren -> loaded_2d_textures,
                                texture2DListItem( tex_num ) );

    return ( Texture2D ) tex_num;
}

Texture2D_List_Item* texture2DListItem( Texture2D tex )
{
    Texture2D_List_Item* li = calloc( 1, sizeof( Texture2D_List_Item ) );
    li -> tex = tex;
    return li;
}

void texture2DListItemDestroy( Texture2D_List_Item* to_destroy )
{
    free( to_destroy );
}

// returns to_prepend
Texture2D_List_Item* texture2DListPrepend( Texture2D_List_Item* to_prepend_to,
        Texture2D_List_Item* to_prepend
                                         )
{
    to_prepend -> next = to_prepend_to;
    return to_prepend;
}

void texture2DListAppend( Texture2D_List_Item* to_append_to
                          , Texture2D_List_Item* to_append
                        )
{
    for ( Texture2D_List_Item* li = to_append_to; li != NULL; li = li -> next ) {
        if ( li -> next ) {
            // do nothing and continue
        } else {
            // append element
            li -> next = to_append;
            break;
        }
    }
}
