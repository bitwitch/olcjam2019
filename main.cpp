#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"

class Game : public olc::PixelGameEngine
{
public:
    input Input;
    player Player;

public:
    Game()
    {
        sAppName = "Destruction";
    }

    bool OnUserCreate() override 
    {
        Input = {};

        Player = {}; 
        Player.position = { 100, 100 };
        Player.width = 9;
        Player.height = 25;
        Player.speedHoriz = 250.0f;
        Player.jumpSpeed = 6000.0f;
        Player.canJump = false;
        Player.grounded = false;
        Player.gravity = 200.0f;
        Player.pge = this;

        return true;    
    }

    bool OnUserUpdate(float fElapsedTime) override 
    {
        Clear(olc::BLACK);
        Input.left = GetKey(olc::Key::LEFT).bHeld;
        Input.right = GetKey(olc::Key::RIGHT).bHeld;
        Input.space = GetKey(olc::Key::SPACE).bPressed;

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

