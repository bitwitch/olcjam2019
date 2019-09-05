#include "World.h"

void world::Update(f32 dt) {
    for (auto platform : platformsStatic) {
        // draw
        pge->FillRect(platform.x, platform.y, platform.w, platform.h, olc::DARK_RED);
    }
}
