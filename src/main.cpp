// #include <iostream>
//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#define WIDTH_FACTOR 16
#define HEIGHT_FACTOR 9
#define SCALE 100



//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// Current displayed PNG image
// SDL_Surface* gPNGSurface = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;



//Screen dimension constants
const int SCREEN_WIDTH = WIDTH_FACTOR * SCALE;
const int SCREEN_HEIGHT = HEIGHT_FACTOR * SCALE;
bool HAS_QUIT = false;
//Apply the image stretched
SDL_Rect stretchRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

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
        //Create window
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
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface( gWindow );
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

	//Destroy Renderer
    SDL_DestroyRenderer( gRenderer );
   
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
	gRenderer = NULL;

    //Quit SDL subsystems
	IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[])
{
	//Initialize SDL
	if (!init())
	{
		printf("Failed to initialize");
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

			while(!HAS_QUIT) {
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

                //Update screen
                SDL_RenderPresent( gRenderer );
			}
		}	
	}
	close();
	return 0;
}