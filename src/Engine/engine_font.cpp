#include "engine_structs.h"
#include "engine_functions.h"

Engine::EngineFont::EngineFont(std::string path, int ptSize)
{
    this->font = Engine::GetFont(path, ptSize);
}

Engine::EngineFont::~EngineFont()
{
    Engine::ReleaseFont(this->font);
    this->font = NULL;
}

Engine::EngineFont::EngineFont()
{
    this->font = NULL;
}

Engine::EngineFont &Engine::EngineFont::operator=(Engine::EngineFont &b)
{
    ///TODO: Do I need a move constructor?
    this->font = b.font;
    b.font = NULL;
    return *this;
}