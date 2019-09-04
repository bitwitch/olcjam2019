#include "Player.h"

void player::Update (input Input, f32 dt) {
// get players intention
    left = Input.left;
    right = Input.right;
    jump = Input.space;

// check collisions
    // if collide left, left = false
    // if collide right, right = false
    // if collide bottom, grounded = true, canJump = true

    if (position.y > 500) {
        grounded = true;
        canJump = true;
    }



// move player
    if (left && !right) {
        position.x -= speedHoriz * dt;
    } else if (right && !left) {
        position.x += speedHoriz * dt;
    }

    if (canJump && jump) {
        canJump = false;
        grounded = false;
        position.y -= jumpSpeed * dt;
    }

    if (!grounded) {
        position.y += gravity * dt;
    }

// draw
    pge->FillRect(position.x, position.y, width, height, olc::WHITE);
}


