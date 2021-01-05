#include "engine_structs.h"
#include "engine_functions.h"

Engine::EngineFont::EngineFont(std::string path, int ptSize)
{
    this->font = Engine::GetFont(path, ptSize);
}

Engine::EngineFont::~EngineFont()
{
    Engine::ReleaseFont(this->font);
}
