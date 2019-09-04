#ifndef PLAYER_H
#define PLAYER_H

#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"

struct player {
    olc::PixelGameEngine *pge;
    f32 width;
    f32 height;
    olc::Sprite sprite;
    v2 position;
    bool canJump;
    bool left;
    bool right;
    bool jump;
    f32 speedHoriz;
    f32 speedVert;
    f32 jumpSpeed;
    bool grounded;
    f32 gravity;

    void Update(input Input, f32 dt);
};

#endif
