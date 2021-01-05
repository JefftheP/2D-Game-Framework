#include "engine_structs.h"
#include "engine_functions.h"

Engine::EngineRenderedText::EngineRenderedText(std::string text, TTF_Font* font, SDL_Color* color, SDL_Renderer* renderer)
{
    this->texture = Engine::MakeTextureFromText(text, font, color, renderer);
}

Engine::EngineRenderedText::~EngineRenderedText()
{
    Engine::ReleaseTexture(this->texture);
}