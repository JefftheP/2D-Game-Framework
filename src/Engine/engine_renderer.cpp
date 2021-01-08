
#include "engine_structs.h"
// #include <SDL.h>

Engine::EngineRenderer::EngineRenderer()
{
    this->_renderer = NULL;
}

Engine::EngineRenderer::EngineRenderer(SDL_Renderer *renderer)
{
    this->_renderer = renderer;
}

void Engine::EngineRenderer::SetRenderer(SDL_Renderer *renderer)
{
    this->_renderer = renderer;
}

Engine::EngineRenderer::~EngineRenderer()
{
    SDL_Log("renderer freed: %u", this->_renderer);
    // Destroy Renderer
    SDL_DestroyRenderer(this->_renderer);
    this->_renderer = NULL;
}

int Engine::EngineRenderer::RenderStart()
{
    return SDL_RenderClear(this->_renderer);
}

int Engine::EngineRenderer::Render(EngineTexture *texture,
                                   const SDL_Rect *srcRect,
                                   const SDL_Rect *dstRect)
{
    return SDL_RenderCopy(this->_renderer, texture->texture, srcRect, dstRect);
}

int Engine::EngineRenderer::RenderFlip(EngineTexture *texture,
                                       const SDL_Rect *srcRect,
                                       const SDL_Rect *dstRect,
                                       const SDL_RendererFlip flip)
{
    return SDL_RenderCopyEx(this->_renderer, texture->texture, srcRect, dstRect, 0.0f, NULL, flip);
}

int Engine::EngineRenderer::RenderRotate(EngineTexture *texture,
                                         const SDL_Rect *srcRect,
                                         const SDL_Rect *dstRect,
                                         const double angle,
                                         const SDL_Point *rotationPoint,
                                         const SDL_RendererFlip flip)
{
    return SDL_RenderCopyEx(this->_renderer, texture->texture, srcRect, dstRect, angle, rotationPoint, flip);
}

int Engine::EngineRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL_SetRenderDrawColor(this->_renderer, r, b, g, a);
}

int Engine::EngineRenderer::DrawPoint(int x, int y)
{
    return SDL_RenderDrawPoint(this->_renderer, x, y);
}

int Engine::EngineRenderer::DrawPoints(const SDL_Point *points, int count)
{
    return SDL_RenderDrawPoints(this->_renderer, points, count);
}

int Engine::EngineRenderer::DrawLine(const SDL_Point *a, const SDL_Point *b)
{
    return SDL_RenderDrawLine(this->_renderer, a->x, a->y, b->x, b->y);
}

int Engine::EngineRenderer::DrawLines(const SDL_Point *points, int count)
{
    return SDL_RenderDrawLines(this->_renderer, points, count);
}

int Engine::EngineRenderer::DrawRect(const SDL_Rect *rect)
{
    return SDL_RenderDrawRect(this->_renderer, rect);
}

int Engine::EngineRenderer::DrawRects(const SDL_Rect *rects, int count)
{
    return SDL_RenderDrawRects(this->_renderer, rects, count);
}

void Engine::EngineRenderer::RenderFinalize()
{
    SDL_RenderPresent(this->_renderer);
}