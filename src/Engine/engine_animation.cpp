#include "engine_structs.h"

Engine::EngineAnimation::EngineAnimation(EngineTexture *texture, Engine::EngineSprite *sprites, int totalFrames, bool isLooped, Engine::AnimiationOrientation orientation)
{
    this->texture = texture;
    this->sprites = sprites;
    this->totalFrames = totalFrames;
    this->currentFrame = 0;
    this->isLooped = isLooped;
    this->orientation = orientation;
}

Engine::EngineSprite *Engine::EngineAnimation::GetCurrentClip()
{
    return &(this->sprites[this->currentFrame]);
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
