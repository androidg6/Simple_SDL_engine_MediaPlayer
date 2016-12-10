/**
MIT License

Copyright (c) 2016-2017 Nathaniel Dielen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/
#include "cSDL.h"

cSDL::cSDL()
{
    SCREEN_WIDTH = 620;
    SCREEN_HEIGHT = 620;
    SCREEN_TITTLE = "SDL2";

    if( !init()){ printf("Failed to initialize! \n"); }
    else if (!mainLoop()){ printf("Exiting main game loop!! \n"); }
}
cSDL::~cSDL()
{
    SCREEN_WIDTH = 0;
    SCREEN_HEIGHT = 0;
    SCREEN_TITTLE = "";

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow (gWindow);

    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    Mix_Quit();
    #ifdef _SDL_TTF_H
    TTF_Quit();
    #endif // _SDL_TTF_H
    SDL_Quit();
}

bool cSDL::init()
{
    if ( SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("SDL could not initialize video! SDL_Error: %s\n",  SDL_GetError());
        return false;
    }
    else
    {
        //....
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
        gWindow = SDL_CreateWindow(SCREEN_TITTLE.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1 ,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
                return false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer,0x11,0xff,0xff,0xff );
            }
        }
        //Initialize PNG loading
        if( !IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
        {
            printf("Failed to initialize image! IMG_Error: %s \n", IMG_GetError());
            return false;
        }
        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            return false;
        }
        #ifdef _SDL_TTF_H
        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            return false;
        }
        #endif // _SDL_TTF_H
    }
    return true;
}

bool cSDL::mainLoop()
{
    if (!loadMedia())
    {
        printf("Failed to load media!! \n");
        return false;
    }
    else
    {
        while(e.type != SDL_QUIT)
        {
            handleEvent();
            doLogic();

            //clearScreen
            SDL_SetRenderDrawColor( gRenderer,0x11,0xff,0xff,0xff );
            SDL_RenderClear( gRenderer );

            render();

            //update
            SDL_RenderPresent( gRenderer );
        }
    }
    cleanUp();
    return true;
}
