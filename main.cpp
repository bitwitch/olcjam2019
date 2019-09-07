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
        sAppName = "Cathedral";
    }

    bool OnUserCreate() override 
    {
        Input = {};

        Player = {}; 
        //Player.sprite =  olc::Sprite("player.png");
        Player.width = 9;
        Player.height = 25;
        Player.position = { 100, 470 };
        Player.health = 3;
        Player.damageSleep = 0.967f;
        Player.accelHoriz = 4.2f;
        Player.jumpForce = 1.2f; // the initial jump
        Player.jumpAccel = 2.36f; // the continued accel after initial jump; hang time
        Player.maxVelocity = { 3.0f, 4.0f };
        Player.gravity = 2.0f;
        Player.frictionGround = 0.01f;
        Player.frictionAir = 0.0005f;
        Player.canJump = false;
        Player.maxJumpTime = 0.2576f;
        Player.wallJumpTimeBuffer = 0.566f;
        Player.grounded = false;
        Player.world = &World;
        Player.pge = this;

        World = {};
        World.pge = this;
        World.player = &Player;
        World.camera = V2(0.0f, 0.0f);
        World.fallDelay = 0.5f;
        World.shake = 0.0f;

        // TODO(shaw): create a better way of constructing the world
        platform Ground = {
            { 5.0f, 500.0f, (f32)ScreenWidth() - 10.0f, 25.0f },
            0.0f
        };
        platform WallLeft = {
            { 5.0f, 0.0f, 25.0f, (f32)ScreenHeight() },
            0.0f
        };
        platform WallRight = {
            { (f32)(ScreenWidth() - 25.0f - 5.0f), 0.0f, 25.0f, (f32)ScreenHeight() },
            0.0f
        };

        World.platformsStatic.push_back(Ground);
        World.platformsStatic.push_back(WallLeft);
        World.platformsStatic.push_back(WallRight);

        return true;    
    }

    bool OnUserUpdate(float fElapsedTime) override 
    {

        // TODO(shaw): make sure this works
        if (GetKey(olc::Key::R).bPressed) {
            OnUserCreate();            
        }

        Input.left = GetKey(olc::Key::LEFT).bHeld;
        Input.right = GetKey(olc::Key::RIGHT).bHeld;
        Input.spaceHeld = GetKey(olc::Key::SPACE).bHeld;
        Input.spaceReleased = GetKey(olc::Key::SPACE).bReleased;

        Clear(olc::BLACK);

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


