#pragma once

#include "game_structs.h"

#define DEFAULT_TIME_STEP 0.016666666666666666

namespace Game
{
    float Move(SDL_Point *p, Vector2D *v, float initSpeed, float accelearation = 0.f, float time = DEFAULT_TIME_STEP);
}