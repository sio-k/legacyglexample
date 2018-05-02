#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

#include "std.h"

// NOTE: Will fail before creating at least one valid OpenGL context!
void initializeGLEW();

void glVersionCheck();

void glFeatureCheck();
