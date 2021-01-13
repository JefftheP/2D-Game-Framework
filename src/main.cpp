#include "Engine/engine_functions.h"
#include "Engine/engine_structs.h"
#include "Engine/engine_defines.h"
#include "Game/game_structs.h"
#include "Game/game_functions.h"

const int SCREEN_WIDTH = WIDTH_FACTOR * SCALE;
const int SCREEN_HEIGHT = HEIGHT_FACTOR * SCALE;

bool initialized;

#define INTRO_FRAMES 20
#define IDLE_FRAMES 13
#define BROCK_Y 600
#define BROCK_X 250

SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

int main(int argc, char *argv[])
{
	const char *name = "SDL Game";
	SDL_Rect windowRect = {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};
	Uint32 windowFlags = SDL_WINDOW_SHOWN;
	Uint32 renderFlags = SDL_RENDERER_ACCELERATED;
	SDL_Color baseColor = {0xFF, 0xFF, 0xFF, 0xFF};
	SDL_Color baseTextColor = {0, 0, 0, 0};

	unsigned int targetTicksPerSecond = 60;
	EngineInfo info = {name, windowRect, windowFlags, renderFlags, baseColor, &baseTextColor, targetTicksPerSecond};
	int init_code = Engine::EngineInit(&info);
	initialized = init_code == 0;
	SDL_Log("initialized: %u", initialized);

	if (initialized)
	{
		Game::Init();
		Game::SetCamera(&camera);
		// SDL_RenderSetLogicalSize(renderer->_renderer, 1600, 900);
		Engine::EngineRun(Game::Update);
	}
	return 0;
}