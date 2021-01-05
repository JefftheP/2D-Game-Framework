#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace Engine {
    struct EngineTimer {
        Uint32 startTime;
        EngineTimer();
        void reset();
        // ms level granularity because of SDL
        Uint32 getTimeSinceStart();
    };

    struct EngineRef {
        //The window we'll be rendering to
        SDL_Window* Window = NULL;
        //The window renderer
        SDL_Renderer* WindowRenderer = NULL;
        EngineTimer timer;
        unsigned int msPerTick;
    };

    struct EngineTexture {
        EngineTexture(std::string path, SDL_Renderer* render = NULL);
        ~EngineTexture();
        SDL_Texture* texture;
    };

    struct EngineFont {
        EngineFont(std::string path, int ptSize);
        ~EngineFont();
        TTF_Font* font;
    };

    struct EngineRenderedText {
        SDL_Texture* texture;
        EngineRenderedText(std::string text, TTF_Font* font, SDL_Color* color = NULL, SDL_Renderer* render = NULL);
        ~EngineRenderedText();
    };


    struct EngineTick {
        Uint32 tick;
        float delta;
    };
}

struct EngineInfo {
    const char* name;
    SDL_Rect windowRect;
    Uint32 windowFlags;
    Uint32 renderFlags;
    SDL_Color baseColor;
    unsigned int targetTicksPerSecond;
};
