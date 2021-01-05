#include "Engine/engine_functions.h"
#include "Engine/engine_structs.h"
#include "Engine/engine_defines.h"

const int SCREEN_WIDTH = WIDTH_FACTOR * SCALE;
const int SCREEN_HEIGHT = HEIGHT_FACTOR * SCALE;

bool initialized;

int GameUpdate(Engine::EngineTick *tick)
{
	// TODO: Need event convention that is not Direct SDL utilization
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		// User requests quit
		if (e.type == SDL_QUIT)
		{
			Engine::Stop();
		}
	}
	
	// SDL_Log("initialized:", initialized);
	return 0;
}

int main(int argc, char *argv[])
{
	const char *name = "SDL Game";
	SDL_Rect windowRect = {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};
	Uint32 windowFlags = SDL_WINDOW_SHOWN;
	Uint32 renderFlags = SDL_RENDERER_ACCELERATED;
	SDL_Color baseColor = {0xFF, 0xFF, 0xFF, 0xFF};
	unsigned int targetTicksPerSecond = 60;
	EngineInfo info = {name, windowRect, windowFlags, renderFlags, baseColor, targetTicksPerSecond};
	int init_code = Engine::EngineInit(&info);
	
	initialized = init_code == 0;
	if(initialized){
		Engine::EngineRun(GameUpdate);
	}
	return 0;
	
}