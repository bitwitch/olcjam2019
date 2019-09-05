#pragma once
#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"
#include <vector>

struct world {
    std::vector<rect> platformsFalling;
    std::vector<rect> platformsStatic;

    olc::PixelGameEngine *pge;

    void Update(f32 dt);
};


