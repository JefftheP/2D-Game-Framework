#include "engine_structs.h"

Engine::EngineTimer::EngineTimer(){
    this->reset();
}

void Engine::EngineTimer::reset(){
    this->startTime = SDL_GetTicks();
}

Uint32 Engine::EngineTimer::getTimeSinceStart(){
    return SDL_GetTicks() - this->startTime;
}