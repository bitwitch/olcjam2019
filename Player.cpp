#include "Player.h"

v2 getPenetrationVector(v2 *md) {
    f32 minDist = ABS(0.0f - md[0].x); 
    v2 boundsPoint = V2(md[0].x, 0.0f);

    if (ABS(md[1].x) < minDist) {
        minDist = ABS(md[1].x);
        boundsPoint = V2(md[1].x, 0.0f);
    }
    if (ABS(md[1].y) < minDist) {
        minDist = ABS(md[1].y);
        boundsPoint = V2(0.0f, md[1].y);
    }
    if (ABS(md[0].y) < minDist) {
        minDist = ABS(md[0].y);
        boundsPoint = V2(0.0f, md[0].y);
    }

    return boundsPoint;
}


void player::Update (input Input, f32 dt) {
    
// get players intention
    left  = Input.left;
    right = Input.right;
    
    if (Input.spaceHeld) {
        if (jumpHeldTime < maxJumpTime) {
            jump = true;
            jumpHeldTime += dt;
        } else {
            jump = false;
            canHang = false;
        }
    } else {
        jump = false;
    }

    if (Input.spaceReleased) {
        jumpHeldTime = 0;
        if (!grounded) canHang = false;
    }

    
    // collisions
    collisionHoriz = false;
    for (auto platform : world->platformsStatic) {
        v2 md[2]; // minowski difference md[0] = min, md[1] = max
        md[0] = position - V2(platform.x + platform.w, platform.y + platform.h);
        md[1] = V2(md[0].x + width + platform.w,
                   md[0].y + height + platform.h);

        if (md[0].x <= 0 && 
            md[0].y <= 0 &&
            md[1].x >= 0 &&
            md[1].y >= 0)
        {
            v2 penetration = getPenetrationVector(md);
            position = position - penetration;

            if (penetration.y > 0) {
                grounded = true;
                canJump = true;
                canHang = true;
                velocity.y = 0;
            }
            
            if (penetration.x != 0) {
                collisionHoriz = true;
                velocity.x = 0;
            }

            pge->DrawLine(platform.x+platform.w/2.0f, platform.y+platform.h/2.0f, position.x + width/2.0, position.y + height/2.0f);
        }
    }

// update player velocity
    if (left && !right) {
        velocity.x -= accelHoriz * dt;
        if (velocity.x > maxVelocity.x) {
            velocity.x = maxVelocity.x;
        }
    } else if (right && !left) {
        velocity.x += accelHoriz * dt;
        if (velocity.x < -maxVelocity.x) {
            velocity.x = -maxVelocity.x;
        }
    }

    // friction 
    if (velocity.x > 0.005) {
        velocity.x -= grounded ? frictionGround : frictionAir;
    } else if (velocity.x < -0.005) {
        velocity.x += grounded ? frictionGround : frictionAir;
    } else {
        velocity.x = 0.0f;
    }

    if (canJump && jump) {
        canJump = false;
        grounded = false;
        velocity.y -= jumpForce; // happens in one frame so don't use dt 
    }

    if (canHang && jump) {
        velocity.y -= jumpAccel;
    }

    if (!grounded) {
        velocity.y += gravity * dt;
        if (velocity.y > maxVelocity.y) {
            velocity.y = maxVelocity.y;
        }
    }

// move
    position.x += velocity.x;
    position.y += velocity.y;

// draw
    pge->FillRect(position.x, position.y, width, height, olc::WHITE);
}



