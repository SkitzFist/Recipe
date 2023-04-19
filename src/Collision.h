#ifndef _Collision
#define _Collision

#include "raylib.h"

static constexpr inline bool isColliding(Vector2 mousePos, Vector2 uiPos, Vector2 uiSize){
    return (mousePos.x >= uiPos.x && mousePos.x <= (uiPos.x + uiSize.x) &&
            mousePos.y >= uiPos.y && mousePos.y <= (uiPos.y + uiSize.y));
}

#endif