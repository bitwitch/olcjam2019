#include "World.h"

//v2 getPenetrationVector(v2 *md) {
    //f32 minDist = ABS(0.0f - md[0].x); 
    //v2 boundsPoint = V2(md[0].x, 0.0f);

	//if (ABS(md[1].x) < minDist) {
		//minDist = ABS(md[1].x);
		//boundsPoint = V2(md[1].x, 0.0f);
	//}
	//if (ABS(md[1].y) < minDist) {
		//minDist = ABS(md[1].y);
		//boundsPoint = V2(0.0f, md[1].y);
	//}
	//if (ABS(md[0].y) < minDist) {
		//minDist = ABS(md[0].y);
		//boundsPoint = V2(0.0f, md[0].y);
	//}

	//return boundsPoint;
//}


void world::Update(f32 dt) {
    for (auto platform : platformsStatic) {

        // FIXME
        // collisions
        v2 md[2]; // minowski difference
        md[0] = player.position - V2(platform.x + platform.w, platform.y + platform.h);
        md[1] = V2(md[0].x + player.width + platform.w,
                   md[0].y + player.height + platform.h);

        if (md[0].x <= 0 && 
            md[0].y <= 0 &&
            md[1].x >= 0 &&
            md[1].y >= 0)
        {
            //v2 penetration = getPenetrationVector( V2(0.0f, 0.0f) );
            v2 penetration = V2(0.0f, 0.0f);
            player.position.x -= penetration.x;
            player.position.y -= penetration.y;
            player.position = player.position - penetration;
        }

       
        // draw
        pge->FillRect(platform.x, platform.y, platform.w, platform.h, olc::DARK_RED);
    }
}
