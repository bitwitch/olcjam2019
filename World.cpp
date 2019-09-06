#include "World.h"
#include "Player.h"

void world::Update(f32 dt) {
    // camera
    //camera.x = player->position.x - pge->ScreenWidth()/2.0f;
    camera.y = player->position.y - pge->ScreenHeight()/2.0f;
    if (camera.y > 0) camera.y = 0.0f;

    f32 ScreenX, ScreenY;

// draw static platforms
    for (auto platform : platformsStatic) {

        // draw
        ScreenX = platform.rect.x - camera.x;
        ScreenY = platform.rect.y - camera.y;
        if (ScreenX >= 0 && ScreenX <= pge->ScreenWidth() &&
            ScreenY >= 0 && ScreenY <= pge->ScreenHeight()) 
        {
            pge->FillRect(ScreenX, ScreenY, 
                platform.rect.w, platform.rect.h, olc::DARK_RED);
        }
    }

// spawn new falling platforms
    if (timeToSpawn <= 0) 
    {
        timeToSpawn = fallDelay;

        f32 W = rand() % 88 + 13; // 13 - 100 maybe
        f32 H = rand() % 75 + 25; // 25 - 100 maybe
        f32 X = rand() % pge->ScreenWidth() + 1 - W; // 0 - (screenwidth - w)
        f32 Y = camera.y - H;
        f32 speed = ((f32)rand() / RAND_MAX) + 0.1f; // random range
        rect R = Rect(X,Y,W,H);
        platform Platform;
        Platform.rect = R;
        Platform.speed = speed;
        platformsFalling.push_back(Platform);
    } 
    else 
    {
        timeToSpawn -= dt;
    }


// update falling platforms
    std::vector<platform>::iterator it = platformsFalling.begin();
    while(it != platformsFalling.end()) 
    {
        bool collided = false;

        // collisions
        for (auto platform : platformsStatic) {
            v2 md[2]; // minowski difference md[0] = min, md[1] = max
            md[0] = V2(it->rect.x, it->rect.y) - V2(platform.rect.x + platform.rect.w, 
                                                    platform.rect.y + platform.rect.h);
            md[1] = V2(md[0].x + it->rect.w + platform.rect.w,
                       md[0].y + it->rect.h + platform.rect.h);

            if (md[0].x <= 0 && 
                md[0].y <= 0 &&
                md[1].x >= 0 &&
                md[1].y >= 0)
            {
                v2 penetration = getPenetrationVector(md);
                it->rect.x = it->rect.x - penetration.x;
                it->rect.y = it->rect.y - penetration.y;
                collided = true;
                break;
            }
        }

        // update position
        if (!collided) {
            it->rect.y += it->speed;        
        }

        // draw
        ScreenX = it->rect.x - camera.x;
        ScreenY = it->rect.y - camera.y;
        if (ScreenX >= 0 && ScreenX <= pge->ScreenWidth() &&
            ScreenY >= 0 && ScreenY <= pge->ScreenHeight()) 
        {
            pge->FillRect(ScreenX, ScreenY, 
                it->rect.w, it->rect.h, olc::VERY_DARK_RED);
        }
        
        // update iterator
        if (collided) {
            platformsStatic.push_back(*it);
            it = platformsFalling.erase(it);
        } else { 
            ++it;
        }
    }

}
