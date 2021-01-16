#pragma once

#include "game_structs.h"

namespace Game
{
    void Init();
    int Update(Engine::EngineTick *tick);
    unsigned int ReadInputs();
    int Render();
    int Close();

    void SetCamera(SDL_Rect *camera);
    SDL_Rect *GetCamera();
    unsigned int GetAnimationMod();
    void SetAnimationMod(unsigned int animMod);
    unsigned int GetRenderScale();

    Engine::EngineTexture *GetFrameTexture(Engine::EngineAnimation *animation);
    SDL_Point *GetBoundaryPoint();
} // namespace Game