#pragma once

#include "olcPixelGameEngine.h"
#include "types.h"
#include "witch_math.h"
#include "collisions.h"
#include "World.h"

struct player {
    world *world;
    olc::PixelGameEngine *pge;
    olc::Sprite sprite;

    f32 width;
    f32 height;
    v2 position;
    v2 velocity;
    v2 maxVelocity;
    //v2 acceleration;
    u32 health; 
    f32 timeToDamage;
    f32 damageSleep;
    f32 accelHoriz;
    f32 jumpForce;
    f32 jumpAccel;
    f32 gravity;
    f32 frictionGround;
    f32 frictionAir;
    f32 jumpBuf;
    f32 jumpHeldTime;
    f32 maxJumpTime;
    f32 wallJumpTimeBuffer;
    f32 wallJumpTimer;
    i32 dirPrevWall; // -1 is left, 1 is right, 0 is no collision

    bool canJump;
    bool canHang; // hang time
    bool left;
    bool right;
    bool jump;
    bool grounded;
    bool collisionLeft;
    bool collisionRight;

    void Update(input Input, f32 dt);
    void CollidePlatforms();
  
};

