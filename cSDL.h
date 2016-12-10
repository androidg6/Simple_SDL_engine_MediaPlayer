/*********************************************************************************
cSDL.h
@ Nathaniel Dielen
D:11-9-16

Main part of the SDL app.
Controls loop, Init, ect

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

**********************************************************************************/
#ifndef cSDL_h
#define cSDL_h
#include "stdafx.h"
/*********************************************************************************
Put other includes here:
**********************************************************************************/
#include "cButton.h"
#include "cMediaPlayer.h"
/**********************************************************************************/
class cSDL
{
    public:
        cSDL(); ~cSDL();
    private:
        /*************************************************************************
        * Screen Dimensions
        **************************************************************************/
        int SCREEN_WIDTH; int SCREEN_HEIGHT; std::string SCREEN_TITTLE;
        /*************************************************************************
        * Init SDL
        *************************************************************************/
        bool init();
        /*************************************************************************
        * The MainLoop for the SDL app
        *************************************************************************/
        bool mainLoop();
        /*************************************************************************
        * MainLoop Functions:
        *************************************************************************/
        bool loadMedia(); void doLogic(); void render(); void handleEvent(); void cleanUp();
        /*************************************************************************************
        * Renderer, Window, and event declarations:
        *************************************************************************/
        SDL_Renderer* gRenderer = NULL;SDL_Window* gWindow = NULL; SDL_Event e;
        /************************************************************************
        * Put Other Variables here:
        *************************************************************************/
        cMediaPlayer mediaPlayer;
        /************************************************************************/
};
#endif // cSDL_h
