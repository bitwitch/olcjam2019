#include "Player.h"

void player::Update (input Input, f32 dt) {
    
// get players intention
    left  = Input.left;
    right = Input.right;
    
    // FIXME(shaw): check this works
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

    //printf("jumpHeldTime: %f  canJump: %d\n", jumpHeldTime, canJump);

// check collisions
    //rect Collisions[4] = {};
    //if (collide = checkCollisionLeft()) {
        //left = false;
        //Collisions[0] = collide;
    //} 
    //if (collide = checkCollisionRight()) {
        //right = false;
        //Collisions[1] = collide;
    //}
    // if collide bottom, grounded = true, canJump = true

    if (position.y + height > 500.0f) {
        position.y = 500.0f - height;
        grounded = true;
        canJump = true;
        velocity.y = 0;
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

    // TODO(shaw): jump higher when hold button longer
    if (canJump && jump) {
        canJump = false;
        grounded = false;
        velocity.y -= jumpForce; 
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



