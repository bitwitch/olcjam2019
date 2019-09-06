#include "Player.h"

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
    collisionLeft = false;
    collisionRight = false;
    grounded = false;
    for (auto platform : world->platformsStatic) {
        v2 md[2]; // minowski difference md[0] = min, md[1] = max
        md[0] = position - V2(platform.rect.x + platform.rect.w, platform.rect.y + platform.rect.h);
        md[1] = V2(md[0].x + width + platform.rect.w,
                   md[0].y + height + platform.rect.h);

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
                velocity.x = 0;
                if (penetration.x > 0) {
                    collisionRight = true;
                } else {
                    collisionLeft = true;
                }
            }
            
            // check if right next to a platform
            if (platform.rect.x + platform.rect.w == position.x) {
                collisionLeft = true;
            } else if (platform.rect.x == position.x + width) {
                collisionRight = true;
            }

            if (platform.rect.y == position.y + height) {
                grounded = true;
            }

            if ((collisionLeft || collisionRight) && !grounded && wallJumpTimer <= 0) {
                canJump = true;
                canHang = true;
               if (jump) {
                   wallJumpTimer = wallJumpTimeBuffer;
                   velocity.x += collisionRight ? -jumpForce : jumpForce;
                   velocity.y += jumpForce/2.0f;
               }
            }

            // for debugging
            pge->DrawLine(platform.rect.x+platform.rect.w/2.0f, platform.rect.y+platform.rect.h/2.0f, position.x + width/2.0, position.y + height/2.0f);
        }
    }

    //printf("position(%f, %f)\n", position.x, position.y);

    //TODO(shaw): if player is against wall, and in air, make a minimum velocity
    // required to pull away from the wall and start moving (stick to the wall a bit to aid wall jumping)

// update player velocity
    if (left && !right && !collisionLeft) {
        velocity.x -= accelHoriz * dt;
        if (velocity.x > maxVelocity.x) {
            velocity.x = maxVelocity.x;
        }
    } else if (right && !left && !collisionRight) {
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


    // jumping
    if (wallJumpTimer > 0) {
        wallJumpTimer -= dt;
    } 
    
    if (canJump && jump) {
        wallJumpTimer = grounded ? wallJumpTimeBuffer/2.0f : wallJumpTimeBuffer;
        velocity.y -= jumpForce; // happens in one frame so don't use dt 
        printf("velocity.y: %f\n", velocity.y);
        canJump = false;
        grounded = false;
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

    printf("position(%f, %f)\n", position.x, position.y);

// move
    position.x += velocity.x;
    position.y += velocity.y;

// draw
    f32 ScreenX, ScreenY;    
    ScreenX = position.x - world->camera.x;
    ScreenY = position.y - world->camera.y;
    pge->FillRect(ScreenX, ScreenY, width, height, olc::WHITE);
}



