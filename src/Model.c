/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */
#include "Model.h"

Model* model( size_t num_tris )
{
    Model* m = calloc( 1, sizeof( Model ) );
    modelBuild( m, num_tris );
    return m;
}

void modelBuild( Model* toinit, size_t num_tris )
{
    toinit -> tri_count = num_tris;
    toinit -> tris = malloc( num_tris * sizeof( triangle ) );
}

void modelFreeTris( Model* to_free_tris_of )
{
    free( to_free_tris_of -> tris );
}

void modelDestroy( Model* to_destroy )
{
    modelFreeTris( to_destroy );
    free( to_destroy );
}
