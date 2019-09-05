#pragma once 

#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"
#include "World.h"

struct player {
    olc::PixelGameEngine *pge;
    world *world;

    f32 width;
    f32 height;
    v2 position;
    v2 velocity;
    v2 maxVelocity;
    //v2 acceleration;
    f32 accelHoriz;
    f32 jumpForce;
    f32 jumpAccel;
    bool canJump;
    bool canHang; // hang time
    bool left;
    bool right;
    bool jump;
    bool grounded;
    bool collisionHoriz;
    f32 gravity;
    f32 frictionGround;
    f32 frictionAir;
    f32 jumpBuf;
    f32 jumpHeldTime;
    f32 maxJumpTime;
    f32 wallJumpTimeBuffer;
    f32 wallJumpTimer;
    olc::Sprite sprite;

    void Update(input Input, f32 dt);
};

