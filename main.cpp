#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "World.h"


class Game : public olc::PixelGameEngine
{
public:
    const olc::Pixel BACKGROUND_BLUE = olc::Pixel(32, 38, 63);
    const f32 timePerFrame = 16.6666666;  // in milliseconds

    std::chrono::system_clock::time_point timeNextFrame;

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
        timeNextFrame = std::chrono::system_clock::now();

        Input = {};

        Player = {};
        //Player.sprite =  olc::Sprite("player.png");
        Player.width = 9;
        Player.height = 25;
        Player.position = {{ 150, 470 }};
        Player.health = 3;
        Player.damageSleep = 0.967f;
        Player.accelHoriz = 4.2f;
        Player.jumpForce = 1.2f; // the initial jump
        Player.jumpAccel = 2.36f; // the continued accel after initial jump; hang time
        Player.maxVelocity = {{ 3.0f, 4.0f }};
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
        World.churchWindow = new olc::Sprite("assets/church_window.png");
        World.platformSheet = new olc::Sprite("assets/falling_block_large.png");
        World.churchTop = new olc::Sprite("assets/church_top.png");

        // TODO(shaw): create a better way of constructing the world
        platform Ground = {
            {0.0f, 500.0f, (f32)ScreenWidth(), 25.0f },
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

        v2 window1  = {{ ScreenWidth()*0.25f, 100.0f }};
        v2 window2  = {{ ScreenWidth()*0.75f, 100.0f }};
        v2 window3  = {{ ScreenWidth()*0.25f, -700.0f }};
        v2 window4  = {{ ScreenWidth()*0.75f, -700.0f }};
        v2 window5  = {{ ScreenWidth()*0.25f, -1600.0f }};
        v2 window6  = {{ ScreenWidth()*0.75f, -1600.0f }};
        v2 window7  = {{ ScreenWidth()*0.25f, -2400.0f }};
        v2 window8  = {{ ScreenWidth()*0.75f, -2400.0f }};
        v2 window9  = {{ ScreenWidth()*0.25f, -3300.0f }};
        v2 window10 = {{ ScreenWidth()*0.75f, -3300.0f }};

        World.windows.push_back(window1);
        World.windows.push_back(window2);
        World.windows.push_back(window3);
        World.windows.push_back(window4);
        World.windows.push_back(window5);
        World.windows.push_back(window6);
        World.windows.push_back(window7);
        World.windows.push_back(window8);
        World.windows.push_back(window9);
        World.windows.push_back(window10);

        return true;    
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

        timeNextFrame += std::chrono::milliseconds(1000 / 60); // 60Hz

        // restart
        if (GetKey(olc::Key::R).bPressed) {
            OnUserCreate();            
        }

        if (!Player.win) {
            Input.left = GetKey(olc::Key::LEFT).bHeld;
            Input.right = GetKey(olc::Key::RIGHT).bHeld;
            Input.spaceHeld = GetKey(olc::Key::SPACE).bHeld;
            Input.spaceReleased = GetKey(olc::Key::SPACE).bReleased;

            Clear(BACKGROUND_BLUE);

            World.Update(fElapsedTime);

            Player.Update(Input, fElapsedTime);

        } else {
            Clear(BACKGROUND_BLUE);
            DrawString(200, 200, "You escaped the cathedral!", olc::WHITE, 2);
        }


        //std::cout << std::time(0) << '\n'; // 60 for each second

        // wait for end of frame
        std::this_thread::sleep_until(timeNextFrame);

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
