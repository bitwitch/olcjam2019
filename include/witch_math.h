#pragma once
#include "types.h"

union v2 
{
    struct {
        f32 x, y;
    };
    struct {
        f32 u, v;
    };
    f32 E[2];
};


