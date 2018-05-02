#pragma once
/*
 * Copyright (C) 2017 Sio Kreuzer. All Rights Reserved.
 */

/*
 * Timer with a microsecond resolution.
 *
 * Due to the unsigned 64-bit integer used, overflows after 568 500 years.
 * To be clear: this could run from today until well past the 41st millenium.
 * You can safely treat this timer like one that does not overflow.
 */

#include "std.h"

void timer(); // initialize timer and start it

u64 timer_resolution(); // get timer resolution in n/th of a second
u64 ticks(); // get time since some time, in machine-defined resolution

f64 time(); // get time since some time, in seconds
