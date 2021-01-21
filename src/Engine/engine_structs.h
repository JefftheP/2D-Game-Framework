#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace Engine
{
    struct EngineTimer;
    struct EngineFont;
    struct EngineTick;
    struct EngineTexture;
    struct EngineRenderer;
    struct EngineRenderedText;
    struct EngineRef;
    struct EngineSprite;
    struct EngineAnimation;

    struct EngineTimer
    {
        Uint32 startTime;
        EngineTimer();
        void reset();
        // ms level granularity because of SDL
        Uint32 getTimeSinceStart();
    };

    struct EngineFont
    {
        EngineFont();
        EngineFont(std::string path, int ptSize);
        ~EngineFont();
        TTF_Font *font;
        EngineFont &Engine::EngineFont::operator=(Engine::EngineFont &b);
    };

    struct EngineTick
    {
        Uint32 tick;
        float delta;
    };

    struct EngineTexture
    {
        SDL_Texture *texture;

        EngineTexture(std::string path, SDL_Renderer *render = NULL);
        EngineTexture(std::string text, EngineFont *font, SDL_Color *color = NULL, EngineRenderer *render = NULL);
        EngineTexture();
        EngineTexture(const EngineTexture &engine_texture);
        EngineTexture(EngineTexture &&engine_texture);

        ~EngineTexture();
        void FreeTexture();
        SDL_Texture *SetTexture(std::string path, SDL_Renderer *renderer = NULL);
        EngineTexture &Engine::EngineTexture::operator=(Engine::EngineTexture &b);

        int GetWidth();
        int GetHeight();
    };

    struct EngineRenderer
    {
        SDL_Renderer *_renderer;
        EngineRenderer();
        EngineRenderer(SDL_Renderer *renderer);
        ~EngineRenderer();

        void SetRenderer(SDL_Renderer *renderer);

        int RenderStart();

        int Render(EngineTexture *texture,
                   const SDL_Rect *srcRect = NULL,
                   const SDL_Rect *dstRect = NULL);

        int RenderFlip(EngineTexture *texture,
                       const SDL_Rect *srcRect = NULL,
                       const SDL_Rect *dstRect = NULL,
                       const SDL_RendererFlip flip = SDL_FLIP_NONE);

        int RenderRotate(EngineTexture *texture,
                         const SDL_Rect *srcRect = NULL,
                         const SDL_Rect *dstRect = NULL,
                         const double angle = 0.0f,
                         const SDL_Point *rotationPoint = NULL,
                         const SDL_RendererFlip flip = SDL_FLIP_NONE);

        int SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        int DrawPoint(int x, int y);
        int DrawPoints(const SDL_Point *points, int count);

        int DrawLine(const SDL_Point *a, const SDL_Point *b);
        int DrawLines(const SDL_Point *points, int count);

        int DrawRect(const SDL_Rect *rect);
        int DrawRects(const SDL_Rect *rects, int count);

        int SetRenderTarget(EngineTexture *texture);

        void RenderFinalize();
    };

    enum AnimiationOrientation
    {
        CENTER,
        LEFT
    };

    struct EngineSprite
    {
        SDL_Rect r;
        int xOffset;
        int yOffset;

        EngineSprite();
        EngineSprite(int x, int y, int w, int h, int xOffset = 0, int yOffset = 0);
        ~EngineSprite();
        int GetXOffset(int scale = 1);
        int GetYOffset(int scale = 1);
    };

    struct EngineAnimation
    {
        EngineTexture *texture;
        EngineSprite *sprites;
        int totalFrames;
        int currentFrame;
        bool isLooped;
        AnimiationOrientation orientation;

        EngineAnimation(EngineTexture *texture, EngineSprite *rects, int totalFrames, bool isLooped = false, AnimiationOrientation = AnimiationOrientation::CENTER);
        EngineSprite *GetCurrentClip();
        void Advance();
        void Reset(int frame = 0);
        bool IsComplete();
    };

    struct EngineRef
    {
        //The window we'll be rendering to
        SDL_Window *Window = NULL;
        //The window renderer
        EngineRenderer *WindowRenderer = NULL;
        EngineTimer *timer = NULL;
        unsigned int msPerTick;
    };
} // namespace Engine

struct EngineInfo
{
    const char *name;
    SDL_Rect windowRect;
    Uint32 windowFlags;
    Uint32 renderFlags;
    SDL_Color baseColor;
    SDL_Color *baseTextColor;
    unsigned int targetTicksPerSecond;
};
