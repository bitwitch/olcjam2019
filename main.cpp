#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "World.h"

class Game : public olc::PixelGameEngine
{
public:
    input Input;
    player Player;
    world World;

public:
    Game()
    {
        sAppName = "Destruction";
    }

    bool OnUserCreate() override 
    {
        Input = {};

        Player = {}; 
        Player.width = 9;
        Player.height = 25;
        Player.position = { 100, 10 };
        //Player.acceleration = { 4.0f, 10.0f };
        Player.accelHoriz = 4.0f;
        Player.jumpForce = 1.0f; // the initial jump
        Player.jumpAccel = 5.0f; // the continued accel after initial jump; hang time
        Player.maxVelocity = { 700.0f, 700.0f };
        Player.gravity = 2.0f;
        Player.frictionGround = 0.007f;
        Player.frictionAir = 0.0005f;
        Player.canJump = false;
        Player.maxJumpTime = 0.235f;
        Player.grounded = false;
        Player.pge = this;

        World = {};
        World.pge = this;
        World.player = Player;

        rect ground = { 0.0f, 500.0f, (f32)ScreenWidth(), 25.0f };

        rect wallLeft = { 0.0f, 0.0f, 25.0f, (f32)ScreenHeight() };
        rect wallRight = { (f32)(ScreenWidth() - 25.0f), 0.0f, 25.0f, (f32)ScreenHeight() };

        World.platformsStatic.push_back(ground);
        World.platformsStatic.push_back(wallLeft);
        World.platformsStatic.push_back(wallRight);

        return true;    
    }

    bool OnUserUpdate(float fElapsedTime) override 
    {
        Clear(olc::BLACK);
        Input.left = GetKey(olc::Key::LEFT).bHeld;
        Input.right = GetKey(olc::Key::RIGHT).bHeld;
        Input.spaceHeld = GetKey(olc::Key::SPACE).bHeld;
        Input.spaceReleased = GetKey(olc::Key::SPACE).bReleased;

        World.Update(fElapsedTime);

        Player.Update(Input, fElapsedTime);

        return true;    
    }

    bool OnUserDestroy() override 
    {
        return true;    
    }
};


int main () {
    Game game;
    if (game.Construct(800, 600, 1, 1)) {
        game.Start();
    }
    return 0;
}


