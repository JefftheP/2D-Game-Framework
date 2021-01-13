#include "engine_structs.h"
#include "engine_functions.h"

Engine::EngineTexture &Engine::EngineTexture::operator=(Engine::EngineTexture &b)
{
    this->texture = b.texture;
    b.texture = NULL;
    return *this;
}

Engine::EngineTexture::EngineTexture(std::string path, SDL_Renderer *renderer)
{
    this->texture = Engine::GetTexture(path, renderer);
}

Engine::EngineTexture::EngineTexture(std::string text, EngineFont *font, SDL_Color *color, Engine::EngineRenderer *renderer)
{
    this->texture = Engine::MakeTextureFromText(text, font->font, color, renderer);
}

Engine::EngineTexture::EngineTexture(const EngineTexture &engine_texture)
{
    SDL_Log("Copy constructor called");
}

Engine::EngineTexture::EngineTexture(EngineTexture &&engine_texture)
{
    SDL_Log("move constructor called");
    this->texture = engine_texture.texture;
    engine_texture.texture = NULL;
}

Engine::EngineTexture::~EngineTexture()
{
    if (this->texture != NULL)
    {
        SDL_Log("texture freed: %u", this->texture);
        Engine::ReleaseTexture(this->texture);
    }
}

Engine::EngineTexture::EngineTexture()
{
    this->texture = NULL;
}

void Engine::EngineTexture::FreeTexture()
{
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}

SDL_Texture *Engine::EngineTexture::SetTexture(std::string path, SDL_Renderer *renderer)
{
    this->FreeTexture();
    this->texture = Engine::GetTexture(path, renderer);
    return this->texture;
}

int Engine::EngineTexture::GetWidth()
{
    if (this->texture == NULL)
        return 0;

    Uint32 format;
    int access;
    int w;
    int h;

    SDL_QueryTexture(this->texture, &format, &access, &w, &h);
    return w;
}

int Engine::EngineTexture::GetHeight()
{
    if (this->texture == NULL)
        return 0;

    Uint32 format;
    int access;
    int w;
    int h;

    SDL_QueryTexture(this->texture, &format, &access, &w, &h);
    return h;
}
