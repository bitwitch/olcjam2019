#pragma once

#include "types.h"
#include <stdlib.h>

#define ABS(N) ((N<0)?(-N):(N))

struct rect {
    f32 x, y, w, h;
};

inline rect
Rect(f32 X, f32 Y, f32 W, f32 H)
{
    rect Result;
    Result.x = X;
    Result.y = Y;
    Result.w = W;
    Result.h = H;
    return Result;
}

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

inline v2 
V2(f32 X, f32 Y) {
    v2 Result;
    Result.x = X;
    Result.y = Y;
    return Result;
}

inline v2 
operator+(v2 A, v2 B)
{
    v2 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    return Result;
}

inline v2 
operator-(v2 A, v2 B)
{
    v2 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    return Result;
}

f32 frand();
