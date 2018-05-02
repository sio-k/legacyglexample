#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

/*
 * This file must be distributed with the binary build of the game engine!
 */

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct Semantic_Version
{
    size_t major_version;
    size_t minor_version;
    size_t patch_version;
} Semantic_Version;

// engine interface towards mods
typedef struct Engine_Interface
{
    Semantic_Version version;

    // memory allocation
    void* ( *engine_malloc )( size_t bytes_to_alloc );
    void* ( *engine_calloc )( size_t arr_length, size_t bytes_per_elem );
    void  ( *engine_free )( void* to_free );

    // I/O
    void  ( *engine_puts )( const char* str );
    void  ( *engine_log )( const char* str );

    // model/tex loading related
    void* ( *engine_load_model_collada )( const char* path );
    void* ( *engine_load_texture )( const char* path );
} Engine_Interface;

// mod interface towards engine
typedef struct Mod_Interface
{
    Semantic_Version version;
    // mod name; doesn't have to be unique
    char identifier[1024];

    // for SDL_TRUE: is a loader and used to load a specific file type
    SDL_bool is_loader;
    // loader function that loads data of this type
    void* ( *loader_function )( const char* path );
    void  ( *loader_free ) ( void* loaded_object );

    // file extension type
    char* file_extension;
    char* file_type_name;

    // pointer to what in-engine type that is output by the loader
    char* output_type_name;

    // mod main function (not main(), main() emits this struct)
    int ( *mod_main )( int argc, char** argv, size_t envc, char** envv_names,
                       char** envv );
} Mod_Interface;

/*
 * Mod loading/init steps:
 *  0. mod's main.c gets compiled
 *  1. mod's main() is called:
 *      0. arguments given:
 *          0. mod name in argv[0]
 *          1. pointer to allocated Mod_Interface struct to be filled by the mod
 *      1. any required global mod state is initialized
 *      2. the mod's Mod_Interface struct is initialized
 *      3. return any non-zero value for success, zero for failure to init
 *  2. Mod is ready to be used.
 */

/*
 * Mods are used by the engine in the following manner(s):
 *  0. Loaders: do not have their mod_main called ever. Called in an arbitrary thread.
 *  1. Anything else: has it's mod_main called every single frame in an arbitrary thread.
 */

/*
 * Any mod's mod_main function.
 *
 * argc: argument count
 * argv: arguments:
 *          [0] == mod name
 *          rest: usually unused.
 *
 * envc:       environment variable count
 * envv_names: environment variable names
 * envv:       environment variables themselves
 *
 * Environment variables are globals in the engine. All globals, with no exceptions. Detailed information about them is given in the documentation.
 */
typedef int ( *modMain )(
    int argc, char** argv, size_t envc, char** envv_names, char** envv );

/*
 * Mod file structure:
 * ModName directory
 * ModName/dependencies.mdeps -> one library name per line
 * ModName/main.c -> main(), only file that gets compiled (so only unity builds are supported)
 */
