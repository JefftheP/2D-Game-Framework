#pragma once

#include "game_structs.h"

namespace Game
{
    bool LineCollidesWithRect(Game::GameLine *line, SDL_Rect *rect);
} // namespace Game