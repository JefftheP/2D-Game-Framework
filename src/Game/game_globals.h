#pragma once
#include "game_structs.h"

namespace Game
{
    SDL_Rect *CAMERA;
    float RENDER_SCALE = 2.f;
    unsigned int ANIMATION_MOD = 3;
    const float deltaT = 0.016666666666666666; // 60FPS lockstep
} // namespace Game
