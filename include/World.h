#pragma once
#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"
#include "collisions.h"
#include <vector>

struct player;

struct platform {
    rect rect;
    f32 speed;
    olc::Sprite *sprite;
};

struct world {
    v2 camera;
    f32 fallDelay;
    f32 timeToSpawn;
    f32 shake;

    std::vector<platform> platformsFalling;
    std::vector<platform> platformsStatic;
    std::vector<v2> windows;

    olc::Sprite *churchWindow;
    olc::Sprite *churchTop;
    olc::Sprite *platformSheet;
    olc::PixelGameEngine *pge;
    player *player;

    void Update(f32 dt);
};


