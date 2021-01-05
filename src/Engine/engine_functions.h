#include "engine_structs.h"
#include "engine_structs.h"

#include <SDL_ttf.h>
#include <string>

namespace Engine {
     int EngineInit(EngineInfo* info);
     int EngineRun(int (*gameUpdate)(Engine::EngineTick*));
     int EngineClose(int GameReturnCode);

     SDL_Texture* GetTexture(std::string path, SDL_Renderer* renderer = NULL); 
     void ReleaseTexture(SDL_Texture* texture);

     TTF_Font* GetFont(std::string path, int ptSize);
     void ReleaseFont(TTF_Font* font);

     SDL_Texture* MakeTextureFromText(std::string text, TTF_Font* font, SDL_Color* color = NULL, SDL_Renderer* render = NULL);
     void Stop();
}