#include "engine_functions.h"
#include "engine_globals.h"
#include "engine_structs.h"
#include "engine_defines.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define AUDIO_FREQUENCY 44100
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS 2
#define AUDIO_CHUNKSIZE 2048

// extern bool Engine::EngineIsRunning;
// extern Engine::EngineRef Engine::_;
// extern SDL_Color Engine::DEFAULT_TEXT_COLOR;

int Engine::EngineInit(EngineInfo *info)
{
    int statusCode = 0;

    if (info->baseTextColor != NULL)
    {
        Engine::DEFAULT_TEXT_COLOR = {
            info->baseTextColor->r,
            info->baseTextColor->b,
            info->baseTextColor->g,
            info->baseTextColor->a};
    }

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
        return FAILED_TO_INITIALIZE_SDL;

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        SDL_Log("Warning: Linear texture filtering not enabled!");
    }

    SDL_Window *window = SDL_CreateWindow(info->name, info->windowRect.x, info->windowRect.y, info->windowRect.w, info->windowRect.h, info->windowFlags);
    if (window == NULL)
        return FAILED_TO_CREATE_WINDOW;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, info->renderFlags);
    if (renderer == NULL)
        return FAILED_TO_CREATE_RENDERER;

    SDL_SetRenderDrawColor(renderer, info->baseColor.r, info->baseColor.b, info->baseColor.g, info->baseColor.a);

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
        return FAILED_TO_INITIALIZE_IMAGES;

    if (TTF_Init() == -1)
        return FAILED_TO_INITIALIZE_FONTS;

    Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE);

    unsigned int msPerTick = (unsigned int)((1.0f / (float)info->targetTicksPerSecond) * 1000);
    Engine::_.Window = window;
    SDL_Log("before");
    Engine::_.WindowRenderer.SetRenderer(renderer);
    SDL_Log("after");
    Engine::_.timer = Engine::EngineTimer();
    Engine::_.msPerTick = msPerTick;
    /// TODO: Need a mechanism for creating Joystick References and passing them back to the game

    return 0;
}

int Engine::EngineRun(int (*gameUpdate)(Engine::EngineTick *))
{
    int returnCode = 0;
    Uint32 delta = 0, sum = 0, start = 0, end = 0, fullDuration = 0;

    while (Engine::EngineIsRunning)
    {
        start = SDL_GetTicks();
        delta = start - Engine::LAST_TICK_TIME;
        Engine::LAST_TICK_TIME = SDL_GetTicks();

        Engine::TICK.tick = ++Engine::CURRENT_TICK;
        Engine::TICK.delta = delta;

        returnCode = gameUpdate(&Engine::TICK);

        if (TPTCOUNTER == TICKS_BUFFER_SIZE)
            TPTCOUNTER = 0;
        Engine::TIME_PER_TICK_BUFFER[Engine::TPTCOUNTER++] = delta;

        sum = 0;
        for (int i = 0; i < TICKS_BUFFER_SIZE; i++)
        {
            sum += TIME_PER_TICK_BUFFER[i];
        }
        Engine::AVERAGE_TICKS_DELTA = (float)sum / (float)TICKS_BUFFER_SIZE;
        float tps = 1000.0f / Engine::AVERAGE_TICKS_DELTA;
        SDL_Log("Tick: %u | ms/tick: %f | TPS: %f | delta: %u", Engine::CURRENT_TICK, Engine::AVERAGE_TICKS_DELTA, tps, delta);

        end = SDL_GetTicks();
        fullDuration = end - start;
        if (fullDuration < Engine::_.msPerTick)
        {
            SDL_Delay(Engine::_.msPerTick - fullDuration);
        }
        else
        {
            SDL_Log("Skipped delay :%u | %u", fullDuration, Engine::_.msPerTick);
        }
    }

    return EngineClose(returnCode);
}

int Engine::EngineClose(int gameReturnCode)
{
    Engine::_.WindowRenderer.~EngineRenderer();

    // Destroy window
    SDL_DestroyWindow(Engine::_.Window);
    Engine::_.Window = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    // TODO Need a mechanism for releasing Joystick references
    // SDL_JoystickClose( gGameController );

    return gameReturnCode;
}

SDL_Texture *Engine::GetTexture(std::string path, SDL_Renderer *renderer)
{
    if (renderer == NULL)
    {
        renderer = Engine::_.WindowRenderer._renderer;
        SDL_Log("renderer pointer: %u", renderer);
    }

    SDL_Texture *texture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        /// TODO: Figure out when we want to do this. Either for all PNGs/Transparent image types. or if a flag is passed
        int m_real_width = loadedSurface->w, m_real_height = loadedSurface->h;
        if (loadedSurface->format->BytesPerPixel == 4)
        {
            Uint8 *pixels = (Uint8 *)loadedSurface->pixels;
            for (int y = 0; y < m_real_height; ++y)
            {
                for (int x = 0; x < m_real_width; ++x)
                {
                    int index = y * loadedSurface->pitch + x * loadedSurface->format->BytesPerPixel;
                    auto target_pixel = (SDL_Color *)&pixels[index];
                    target_pixel->r = (Uint8)(target_pixel->r * target_pixel->a / 255.0);
                    target_pixel->g = (Uint8)(target_pixel->g * target_pixel->a / 255.0);
                    target_pixel->b = (Uint8)(target_pixel->b * target_pixel->a / 255.0);
                }
            }
        }

        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_BlendMode target = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, SDL_BLENDOPERATION_ADD, SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, SDL_BLENDOPERATION_ADD);
        SDL_SetTextureBlendMode(texture, target);

        if (texture == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return texture;
}

void Engine::ReleaseTexture(SDL_Texture *texture)
{
    //Free loaded image
    SDL_DestroyTexture(texture);
    texture = NULL;
}

TTF_Font *Engine::GetFont(std::string path, int ptSize)
{
    return TTF_OpenFont(path.c_str(), ptSize);
}

void Engine::ReleaseFont(TTF_Font *font)
{
    TTF_CloseFont(font);
    font = NULL;
}

SDL_Texture *Engine::MakeTextureFromText(std::string text, TTF_Font *font, SDL_Color *color, EngineRenderer *renderer)
{
    if (color == NULL)
    {
        color = &Engine::DEFAULT_TEXT_COLOR;
    }

    if (renderer == NULL)
    {
        renderer = &Engine::_.WindowRenderer;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), *color);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer->_renderer, textSurface);
    if (newTexture == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    return newTexture;
}

void Engine::Stop()
{
    Engine::EngineIsRunning = false;
}

Engine::EngineRenderer *Engine::GetWindowRenderer()
{
    return &Engine::_.WindowRenderer;
}