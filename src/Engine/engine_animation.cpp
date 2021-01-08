#include "engine_structs.h"

Engine::EngineAnimation::EngineAnimation(EngineTexture *texture, SDL_Rect *rects, int totalFrames)
{
    this->texture = texture;
    this->rects = rects;
    this->totalFrames = totalFrames;
    this->currentFrame = 0;
}

SDL_Rect *Engine::EngineAnimation::GetCurrentClip()
{
    return &(this->rects[this->currentFrame]);
}

void Engine::EngineAnimation::Advance()
{
    /// TODO: Maybe a flag for looping animations so that they can flip back to 0 once the animation is complete;
    if (this->currentFrame < this->totalFrames - 1)
    {
        this->currentFrame++;
    }
}

void Engine::EngineAnimation::Reset(int frame)
{
    if (frame < this->totalFrames)
    {
        this->currentFrame = frame;
    }
    else
    {
        SDL_Log("Attempted to reset animation to an invalid index");
    }
}