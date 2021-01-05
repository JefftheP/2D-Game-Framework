#pragma once

#include "engine_defines.h"
#include "engine_structs.h"

#include <SDL.h>

namespace Engine {
    // TODO: Decide how I want to handle this, dont exactly like the idea of this just floating around
    bool EngineIsRunning = true;
    
    Engine::EngineRef _;
    
    SDL_Color DEFAULT_TEXT_COLOR = {0,0,0};
    
    // Array of deltas from tick to tick 
    Uint32 TIME_PER_TICK_BUFFER[TICKS_BUFFER_SIZE] = {};

    unsigned char TPTCOUNTER = 0;

    // Count of all ticks since initialized
    Uint32 CURRENT_TICK = 0;

    Uint32 LAST_TICK_TIME = 0;

    float AVERAGE_TICKS_DELTA = 0.0f;

    EngineTick TICK = {0, 0.0f};
}