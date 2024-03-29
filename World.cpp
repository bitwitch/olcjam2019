#include "World.h"
#include "Player.h"

void world::Update(f32 dt) 
{
// camera
    camera.y = player->position.y - pge->ScreenHeight()/2.0f;
    if (camera.y > 0) camera.y = 0.0f;

    // currently camera only moves vertically
    // uncomment to allow horizontal movement, will need to 
    // implement horizontal camera bounds first
    //
    //camera.x = player->position.x - pge->ScreenWidth()/2.0f;
    
    // random chance of screen shake
    if (frand() > 0.995f) {
        shake = 5.0f;
    }
    
    if (shake > 0.005f) {
        camera.x += (frand() * 2.0f * shake) - shake; 
        camera.y += (frand() * 2.0f * shake) - shake; 
        shake *= 0.9;
    } else {
        camera.x = 0.0f;
    }

    f32 ScreenX, ScreenY;

// draw church top if visible
    if (camera.y < -3800) {
        pge->DrawSprite(pge->ScreenWidth()/2.0f - 22, -4100 - camera.y, churchTop, 4);
    }

// draw windows
    for (auto window : windows) {
        // draw
        ScreenX = window.x - camera.x;
        ScreenY = window.y - camera.y;

        v2 md[2]; // minowski difference md[0] = min, md[1] = max
        md[0] = V2(ScreenX, ScreenY) - V2(pge->ScreenWidth(), pge->ScreenHeight());
        md[1] = V2(md[0].x + 63 + pge->ScreenWidth(),
                   md[0].y + 240 + pge->ScreenHeight());

        if (md[0].x <= 0 && 
            md[0].y <= 0 &&
            md[1].x >= 0 &&
            md[1].y >= 0)
        {
            pge->DrawSprite(ScreenX, ScreenY, churchWindow, 3);
        }
    }
      

// draw static platforms
    for (auto platform : platformsStatic) {

        // draw
        ScreenX = platform.rect.x - camera.x;
        ScreenY = platform.rect.y - camera.y;


        v2 md[2]; // minowski difference md[0] = min, md[1] = max
        md[0] = V2(ScreenX, ScreenY) - V2(pge->ScreenWidth(), pge->ScreenHeight());
        md[1] = V2(md[0].x + platform.rect.w + pge->ScreenWidth(),
                   md[0].y + platform.rect.h + pge->ScreenHeight());

        if (md[0].x <= 0 && 
            md[0].y <= 0 &&
            md[1].x >= 0 &&
            md[1].y >= 0)
        {
            pge->DrawPartialSprite(ScreenX, ScreenY, platformSheet, 
                0, 0, platform.rect.w, platform.rect.h);
        }
    }

// spawn new falling platforms
    if (timeToSpawn <= 0) 
    {
        timeToSpawn = fallDelay;

        f32 W = rand() % 88 + 12; // 12 - 100 maybe
        f32 H = rand() % 75 + 25; // 25 - 100 maybe
        f32 Y = camera.y - H;
        f32 X;
        
        if (platformsFalling.size() > 0) {
            f32 lastX = platformsFalling.back().rect.x;
            // random range that is within 200 of last platform
            X = (frand() * 400.0f - 200.0f) + lastX; 
            if (X < 0) {
                X = 0.0f;
            } else if (X + W > pge->ScreenWidth()) {
                X = pge->ScreenWidth() - W;
            }
        } else {
            X = rand() % pge->ScreenWidth() + 1 - W; // 0 - (screenwidth - w)
        }

        f32 speed = frand() * 0.5f + 0.1f; // random range
        rect R = Rect(X,Y,W,H);
        platform Platform = {};
        Platform.rect = R;
        Platform.speed = speed;
        Platform.sprite = NULL;
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
        pge->DrawPartialSprite(ScreenX, ScreenY, platformSheet, 0, 0, it->rect.w, it->rect.h);

        // update iterator
        if (collided) {
            platformsStatic.push_back(*it);
            it = platformsFalling.erase(it);
        } else { 
            ++it;
        }
    }

}
