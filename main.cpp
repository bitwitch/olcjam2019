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
        Input = { };
        Player = { 
            .position = { 100, 100 },
            .width = 9,
            .height = 25,
            .speedHoriz = 250.0f,
            .pge = this 
        };
        return true;    
    }

    bool OnUserUpdate(float fElapsedTime) override 
    {
        Clear(olc::BLACK);
        Input.left = GetKey(olc::Key::LEFT).bHeld;
        Input.right = GetKey(olc::Key::RIGHT).bHeld;
        Input.space = GetKey(olc::Key::RIGHT).bHeld;

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

