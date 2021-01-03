// #include <iostream>
//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#define WIDTH_FACTOR 16
#define HEIGHT_FACTOR 9
#define TARGET_FRAME_RATE 60
#define SCALE 100

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

// Texture reference for text
SDL_Texture* mTexture = NULL;


//printed font
TTF_Font* gFont = NULL;

SDL_Color textColor = { 255, 255, 255 };


//Screen dimension constants
const int SCREEN_WIDTH = WIDTH_FACTOR * SCALE;
const int SCREEN_HEIGHT = HEIGHT_FACTOR * SCALE;
bool HAS_QUIT = false;
//Apply the image stretched
SDL_Rect stretchRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
Uint32 TARGET_MS_PER_FRAME = (Uint32) ((1.0f / (float)TARGET_FRAME_RATE) * 1000.0f);
Uint32 INIT_START_TIME = 0;
int TOTAL_COUNTED_FRAMES = 0;
float avgFPS = 0;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual texture
SDL_Texture* loadTexture( std::string path );


bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
		    // Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
			else
			{
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				else
				{
					//Initialize SDL_ttf
					if( TTF_Init() == -1 )
					{
						printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
						success = false;
					}
					else
					{
						//Get window surface
						gScreenSurface = SDL_GetWindowSurface( gWindow );
					}
				}	
			}
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

	//Load PNG surface
	gTexture = loadTexture( "images/loaded.png" );
	if( gTexture == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
	}
	else 
	{
		gFont = TTF_OpenFont("fonts/OpenSans-Bold.ttf", 28 );
		if( gFont == NULL )
		{
			printf( "Failed to load font image!\n" );
			success = false;
		}
	}

    return success;
}

SDL_Texture* loadTexture( std::string path )
{
	//The final optimized image
	SDL_Texture* texture = NULL;
	//Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
	else 
	{
		texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( texture == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

    return texture;
}

void close()
{
    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

	SDL_DestroyTexture( mTexture);
	mTexture = NULL;

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy Renderer
    SDL_DestroyRenderer( gRenderer );
   
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
	gRenderer = NULL;

    //Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[])
{
	//Initialize SDL
	if (!init())
	{
		printf("Failed to initialize\n");
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Event handler
			SDL_Event e;
			Uint32 FrameStartTime = 0;
			Uint32 FrameElapsedTime = 0;
			Uint32 delta = 0;
			Uint32 sleepTime = 0;
			float avgFPS;
			INIT_START_TIME = SDL_GetTicks();

			while(!HAS_QUIT) {
				FrameStartTime = SDL_GetTicks();
				while( SDL_PollEvent( &e ) != 0 )
				{
					// User requests quit
					if( e.type == SDL_QUIT )
					{
						HAS_QUIT = true;
					}
				}

                //Clear screen
                SDL_RenderClear( gRenderer );
				
				// SDL_BlitScaled( gPNGSurface, NULL, gScreenSurface, &stretchRect );

				//Render texture to screen
                SDL_RenderCopy( gRenderer, gTexture, NULL, &stretchRect );

				FrameElapsedTime = SDL_GetTicks();
				delta = FrameElapsedTime - FrameStartTime;

				//Calculate and correct fps
				avgFPS = (++TOTAL_COUNTED_FRAMES / (float)(FrameElapsedTime - INIT_START_TIME)) * 1000.f;
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}
				std::stringstream ss;
				ss << "Frame: " << TOTAL_COUNTED_FRAMES << " | FPS: " << avgFPS << " | delta: " << delta;

				SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, ss.str().c_str(), textColor);
				if( textSurface == NULL )
				{
					printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
				}
				else
				{
					if(mTexture != NULL)
					{
						SDL_DestroyTexture(mTexture);
						mTexture = NULL;
					}
					//Create texture from surface pixels
					mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
					if( mTexture == NULL )
					{
						printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
					}
					int x = 0, y = 0; 
					SDL_Rect* clip = NULL;
					double angle = 0.0;
					SDL_Point* center = NULL; 
					SDL_RendererFlip flip = SDL_FLIP_NONE;
					SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };

					SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
					SDL_FreeSurface( textSurface );
				}
				//Update screen
				SDL_RenderPresent( gRenderer );

				FrameElapsedTime = SDL_GetTicks();
				delta = FrameElapsedTime - FrameStartTime;
				if(delta < TARGET_MS_PER_FRAME) {
					printf("Frame: %u | FPS: %f | delta: %u \n", TOTAL_COUNTED_FRAMES, avgFPS, delta);
					sleepTime = TARGET_MS_PER_FRAME - delta;
					SDL_Delay( sleepTime );
				}
			}
		}
	}
	close();
	return 0;
}