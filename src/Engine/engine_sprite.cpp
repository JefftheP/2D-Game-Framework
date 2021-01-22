#include "engine_structs.h"

Engine::EngineSprite::EngineSprite(Engine::EngineTexture *texture)
{
    this->r.x = 0;
    this->r.y = 0;
    if (texture != NULL)
    {
        this->r.w = texture->GetWidth();
        this->r.h = texture->GetHeight();
    }
    else
    {
        this->r.w = 0;
        this->r.h = 0;
    }
    this->xOffset = 0;
    this->yOffset = 0;
    this->texture = texture;
}

Engine::EngineSprite::EngineSprite(int x, int y, int w, int h, int xOffset, int yOffset, Engine::EngineTexture *texture)
{
    this->r.x = x;
    this->r.y = y;
    this->r.w = w;
    this->r.h = h;
    this->xOffset = xOffset;
    this->yOffset = yOffset;
    this->texture = texture;
}

Engine::EngineSprite::~EngineSprite()
{
    this->r.x = 0;
    this->r.y = 0;
    this->r.w = 0;
    this->r.h = 0;
    this->xOffset = 0;
    this->yOffset = 0;
    if (this->texture != NULL)
    {
        SDL_Log("sprite deleting texture");
        delete this->texture;
    }
    this->texture = NULL;
}

int Engine::EngineSprite::GetXOffset(int scale)
{
    return this->xOffset * scale;
}

int Engine::EngineSprite::GetYOffset(int scale)
{
    return this->yOffset * scale;
}

Engine::EngineSprite &Engine::EngineSprite::operator=(Engine::EngineSprite &b)
{
    this->texture = b.texture;
    SDL_Log("assignemnet called: %u", this->texture);
    this->r.x = b.r.x;
    this->r.y = b.r.y;
    this->r.w = b.r.w;
    this->r.h = b.r.h;
    this->xOffset = b.xOffset;
    this->yOffset = b.yOffset;

    b.texture = NULL;
    return *this;
}
