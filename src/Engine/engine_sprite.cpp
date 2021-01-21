#include "engine_structs.h"

Engine::EngineSprite::EngineSprite()
{
    this->r.x = 0;
    this->r.y = 0;
    this->r.w = 0;
    this->r.h = 0;
    this->xOffset = 0;
    this->yOffset = 0;
}

Engine::EngineSprite::EngineSprite(int x, int y, int w, int h, int xOffset, int yOffset)
{
    this->r.x = x;
    this->r.y = y;
    this->r.w = w;
    this->r.h = h;
    this->xOffset = xOffset;
    this->yOffset = yOffset;
}

Engine::EngineSprite::~EngineSprite()
{
    this->r.x = 0;
    this->r.y = 0;
    this->r.w = 0;
    this->r.h = 0;
    this->xOffset = 0;
    this->yOffset = 0;
}

int Engine::EngineSprite::GetXOffset(int scale)
{
    return this->xOffset * scale;
}

int Engine::EngineSprite::GetYOffset(int scale)
{
    return this->yOffset * scale;
}