#include "engine_structs.h"

Engine::EngineAnimation::EngineAnimation(EngineTexture *texture, SDL_Rect *rects, int totalFrames, bool isLooped, Engine::AnimiationOrientation orientation)
{
    this->texture = texture;
    this->rects = rects;
    this->totalFrames = totalFrames;
    this->currentFrame = 0;
    this->isLooped = isLooped;
    this->orientation = orientation;
}

SDL_Rect *Engine::EngineAnimation::GetCurrentClip()
{
    return &(this->rects[this->currentFrame]);
}

void Engine::EngineAnimation::Advance()
{
    if (this->currentFrame < this->totalFrames - 1)
    {
        this->currentFrame++;
    }
    else if (this->isLooped)
    {
        this->currentFrame = 0;
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

bool Engine::EngineAnimation::IsComplete()
{
    return ((!this->isLooped) && this->currentFrame == this->totalFrames - 1);
}