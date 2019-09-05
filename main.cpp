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
        Player.accelHoriz = 4.0f;
        Player.jumpForce = 1.0f; // the initial jump
        Player.jumpAccel = 0.0136f; // the continued accel after initial jump; hang time
        Player.maxVelocity = { 700.0f, 700.0f };
        Player.gravity = 2.0f;
        Player.frictionGround = 0.01f;
        Player.frictionAir = 0.0005f;
        Player.canJump = false;
        Player.maxJumpTime = 0.235f;
        Player.wallJumpTimeBuffer = 0.566f;
        Player.grounded = false;
        Player.world = &World;
        Player.pge = this;

        World = {};
        World.pge = this;
        World.player = &Player;
        World.camera = V2(0.0f, 0.0f);
        World.fallDelay = 2.0f;

        // TODO(shaw): create a better way of constructing the world
        platform Ground = {
            { 0.0f, 500.0f, (f32)ScreenWidth(), 25.0f },
            0.0f
        };
        platform WallLeft = {
            { 0.0f, 0.0f, 25.0f, (f32)ScreenHeight() },
            0.0f
        };
        platform WallRight = {
            { (f32)(ScreenWidth() - 25.0f), 0.0f, 25.0f, (f32)ScreenHeight() },
            0.0f
        };

        World.platformsStatic.push_back(Ground);
        World.platformsStatic.push_back(WallLeft);
        World.platformsStatic.push_back(WallRight);

        platform Fall0 = {
            { 100.0f, 0.0f, 25.0f, 66.0f },
            0.1f
        };
        platform Fall1 = {
            { 200.0f, 0.0f, 25.0f, 66.0f },
            0.0f
        };
        platform Fall2 = {
            { 300.0f, 0.0f, 25.0f, 66.0f },
            0.0f
        };

        World.platformsFalling.push_back(Fall0);
        World.platformsFalling.push_back(Fall1);
        World.platformsFalling.push_back(Fall2);

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


