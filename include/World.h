#pragma once
#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"
#include "Player.h"
#include <vector>

struct world {
    std::vector<rect> platformsFalling;
    std::vector<rect> platformsStatic;

    olc::PixelGameEngine *pge;

    player player;
    void Update(f32 dt);
};


