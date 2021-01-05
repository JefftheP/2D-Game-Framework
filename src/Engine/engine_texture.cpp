#include "engine_structs.h"
#include "engine_functions.h"

Engine::EngineTexture::EngineTexture(std::string path, SDL_Renderer* renderer)
{
    this->texture = Engine::GetTexture(path, renderer);
}

Engine::EngineTexture::~EngineTexture()
{
    Engine::ReleaseTexture(this->texture);
}