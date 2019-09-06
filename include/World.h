#pragma once
#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"
#include "collisions.h"
#include <stdlib.h>
#include <vector>

struct player;

struct platform {
    rect rect;
    f32 speed;
};

struct world {
    v2 camera;
    f32 fallDelay;
    f32 timeToSpawn;

    std::vector<platform> platformsFalling;
    std::vector<platform> platformsStatic;

    olc::PixelGameEngine *pge;
    player *player;

    void Update(f32 dt);
};


