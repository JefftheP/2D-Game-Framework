#include "Engine/engine_functions.h"
#include "Engine/engine_structs.h"
#include "Engine/engine_defines.h"

const int SCREEN_WIDTH = WIDTH_FACTOR * SCALE;
const int SCREEN_HEIGHT = HEIGHT_FACTOR * SCALE;

bool initialized;
Engine::EngineRenderer *renderer = NULL;
Engine::EngineTexture *bg = NULL;
Engine::EngineTexture *sheet = NULL;
Engine::EngineFont *font = NULL;
Engine::EngineTexture *text;
Engine::EngineAnimation *intro = NULL;
Engine::EngineTexture *currFrame = NULL;

std::string val = "RENDERED TEXT";
SDL_Rect textRect = {};
SDL_Rect brock = {0, 0, 120, 164};
SDL_Rect brockOnScreen = {600, 250, brock.w, brock.h};
SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

#define INTRO_FRAMES 20
#define BROCK_Y 600
#define BROCK_X 250
SDL_Rect introRects[INTRO_FRAMES];

const SDL_Rect screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
int aniCounter = 0;
int scale = 3;
int initialFooting = 0;

void GameClean()
{
	delete currFrame;
	delete renderer;
	delete bg;
	delete sheet;
	delete font;
	delete text;
	delete intro;
}

int GameUpdate(Engine::EngineTick *tick)
{
	/// TODO: Need event convention that is not Direct SDL utilization
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		// User requests quit
		if (e.type == SDL_QUIT)
		{
			Engine::Stop();
		}
	}

	if (intro->currentFrame == intro->totalFrames - 1)
	{
		intro->Reset();
	}
	SDL_Rect *clip = intro->GetCurrentClip();

	SDL_Rect frameRect = {
		brockOnScreen.x + 5,
		brockOnScreen.y + 5,
		currFrame->GetWidth(),
		currFrame->GetHeight()};

	renderer->RenderStart();
	renderer->Render(bg, &camera, &screen);
	renderer->Render(text, &textRect, &textRect);

	brockOnScreen.w = clip->w * scale;
	brockOnScreen.h = clip->h * scale;
	brockOnScreen.y = initialFooting - (clip->h * scale);

	renderer->DrawRect(&brockOnScreen);
	renderer->Render(sheet, clip, &brockOnScreen);
	renderer->Render(currFrame, NULL, &frameRect);

	if (aniCounter % 2 == 0)
	{
		delete currFrame;
		std::string count = std::to_string(intro->currentFrame);
		currFrame = new Engine::EngineTexture(count, font, &white);
		intro->Advance();
	}
	++aniCounter;

	renderer->RenderFinalize();

	return 0;
}

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
		renderer = Engine::GetWindowRenderer();
		bg = new Engine::EngineTexture("images/KOF-XIII-Burnt-Remains-Stage.jpg");
		sheet = new Engine::EngineTexture("images/venom.png");
		font = new Engine::EngineFont("fonts/OpenSans-Bold.ttf", 28);
		text = new Engine::EngineTexture(val, font);
		currFrame = new Engine::EngineTexture(std::to_string(0), font, &white);

		textRect.w = text->GetWidth();
		textRect.h = text->GetHeight();

		int baseX = 8;
		int baseY = 15;
		int rowW = 109;
		int endY = 160;

		// introRects[0] = {baseX, baseY, 109, row0H};
		// introRects[1] = {148, baseY, 109, row0H};
		// introRects[2] = {291, baseY, 109, row0H};
		// introRects[3] = {429, baseY, 111, row0H};
		// introRects[4] = {569, baseY, 112, row0H};
		// introRects[5] = {704, baseY, 115, row0H};
		// introRects[6] = {843, baseY, 116, row0H};
		// introRects[7] = {986, baseY, 124, row0H};

		introRects[0] = {9, baseY, rowW, 0};
		introRects[1] = {148, baseY, rowW, 0};
		introRects[2] = {291, baseY, rowW, 0};
		introRects[3] = {431, 8, rowW, 0};
		introRects[4] = {569, baseY, 112, 0};
		introRects[5] = {704, baseY, 115, 0};
		introRects[6] = {843, baseY, 116, 0};
		introRects[7] = {986, baseY, 124, 0};

		for (int i = 0; i < 8; i++)
		{
			introRects[i].h = endY - introRects[i].y;
		}

		baseX = 7;
		baseY = 173;
		endY = 318;
		rowW = 111;

		introRects[8] = {baseX, baseY, 119, 0};
		introRects[9] = {146, baseY, 112, 0};
		introRects[10] = {277, baseY, rowW, 0};
		introRects[11] = {411, baseY, rowW, 0};
		introRects[12] = {546, baseY, rowW, 0};
		introRects[13] = {679, 173, rowW, 0};
		introRects[14] = {807, baseY, rowW, 0};
		introRects[15] = {942, baseY, rowW, 0};
		introRects[16] = {1075, baseY, rowW, 0};

		for (int i = 8; i < 17; i++)
		{
			introRects[i].h = endY - introRects[i].y;
		}

		baseX = 4;
		baseY = 331;
		endY = 453;

		introRects[17] = {baseX, baseY, 130, 0};
		introRects[18] = {165, baseY, 139, 0};
		introRects[19] = {327, baseY, 143, 0};

		for (int i = 17; i < 20; i++)
		{
			introRects[i].h = endY - introRects[i].y;
		}

		initialFooting = BROCK_Y + introRects[0].h;
		intro = new Engine::EngineAnimation(sheet, introRects, INTRO_FRAMES);

		Engine::EngineRun(GameUpdate);
	}
	return 0;
}