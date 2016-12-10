/*********************************************
cMediaPlayer.h
@ Nathaniel Dielen
D: 11-22-16

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

**********************************************/
#ifndef cMediaPlayer_h
#define cMediaPlayer_h

#include "stdafx.h"
#include "cButton.h"

class cPlayButton : public cSysButton
{
    public:
        cPlayButton(); ~cPlayButton(); void free();
        void draw(SDL_Renderer * gRenderer);
};

class cPauseButton : public cSysButton
{
    public:
        cPauseButton(); ~cPauseButton(); void free();
        void draw(SDL_Renderer * gRenderer);
};

class cNextSongButton : public cSysButton
{
    public:
        cNextSongButton(); ~cNextSongButton(); void free();
        void draw(SDL_Renderer * gRenderer);
};

class cPreviousSongButton : public cSysButton
{
    public:
        cPreviousSongButton(); ~cPreviousSongButton(); void free();
        void draw(SDL_Renderer * gRenderer);
};

class cMediaPlayerButtons
{
    public:
        cMediaPlayerButtons(); ~cMediaPlayerButtons(); void free();

        void setQuad(SDL_Rect * renderQuad);
        void handleEvent(SDL_Event * e);
        void draw(SDL_Renderer * gRenderer);

        int onClick();
        enum {PLAY_BUTTON = 0 , PAUSE_BUTTON ,PREVIOUS_BUTTON , STOP_BUTTON , NEXT_BUTTON , MAX_BUTTONS};

    private:

        cSysButton * buttonArr[MAX_BUTTONS];

};

class cMediaPlayer
{
    public:
        cMediaPlayer(); ~cMediaPlayer(); void free();

        bool loadMedia(SDL_Renderer * gRenderer);

        void handleEvent(SDL_Event * e);

        void render(SDL_Renderer * gRenderer);

    private:

        cMediaPlayerButtons mediaPlayerButtons;
        cTexture background;
        TTF_Font * mFont;
        SDL_Rect highLightQuad;
        SDL_Color yellowHighlight;
        SDL_Color color_black;
        enum {SONG1=0, SONG2,SONG3,SONG4,SONG5,SONG6,SONG7,SONG8,SONG9,SONG10,MAX_SONGS};
        cTexturedTextButton songButton[MAX_SONGS];
        cTexture emptyLable[cTexturedTextButton::TOTAL_TEXTURE];
        int curentSelection;
        cTexture songLable[MAX_SONGS][cTexturedTextButton::TOTAL_TEXTURE];
        Mix_Music* songMusic[MAX_SONGS];
};

#endif // cMediaPlayer_h
