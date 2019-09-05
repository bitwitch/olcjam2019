#include "collisions.h"

v2 getPenetrationVector(v2 *md) {
    f32 minDist = ABS(0.0f - md[0].x); 
    v2 boundsPoint = V2(md[0].x, 0.0f);

    if (ABS(md[1].x) < minDist) {
        minDist = ABS(md[1].x);
        boundsPoint = V2(md[1].x, 0.0f);
    }
    if (ABS(md[1].y) < minDist) {
        minDist = ABS(md[1].y);
        boundsPoint = V2(0.0f, md[1].y);
    }
    if (ABS(md[0].y) < minDist) {
        minDist = ABS(md[0].y);
        boundsPoint = V2(0.0f, md[0].y);
    }

    return boundsPoint;
}

