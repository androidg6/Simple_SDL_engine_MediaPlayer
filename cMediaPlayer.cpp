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

#include "cMediaPlayer.h"

/*****************************************************************************************************/

cPlayButton::cPlayButton(){}
cPlayButton::~cPlayButton(){ free(); }
void cPlayButton::free(){cSysButton::free();}
void cPlayButton::draw(SDL_Renderer * gRenderer)
{
    SDL_Rect renderQuad;

    renderQuad.x = cButton::position.x;
    renderQuad.y = cButton::position.y;
    renderQuad.h = cButton::buttonHeight;
    renderQuad.w = cButton::buttonWidth;

    int numPoints = 4;
    SDL_Point linePoints[numPoints];

    linePoints[0].x = renderQuad.x;
    linePoints[0].y = renderQuad.y;

    linePoints[1].x = renderQuad.x;
    linePoints[1].y = renderQuad.y + renderQuad.h;

    linePoints[2].x = renderQuad.x + renderQuad.w;
    linePoints[2].y = renderQuad.y + renderQuad.h /2;

    linePoints[3].x = renderQuad.x;
    linePoints[3].y = renderQuad.y;

    if( cButton::buttonState == cButton::MOUSE_INSIDE)
    {
           SDL_SetRenderDrawColor(gRenderer , cSysButton::mSelectColor.r, cSysButton::mSelectColor.g, cSysButton::mSelectColor.b, cSysButton::mSelectColor.a );
    }
    else if( cButton::buttonState == cButton::MOUSE_OUTSIDE)
    {
         SDL_SetRenderDrawColor(gRenderer, cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a );
    }
    else if (cButton::buttonState == cButton::DEFAULT)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    else if( cButton::buttonState == cButton::BUTTON_MOUSE_DOWN)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mClickColor.r, cSysButton::mClickColor.g, cSysButton::mClickColor.b, cSysButton::mClickColor.a);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    SDL_RenderDrawLines(gRenderer,linePoints,numPoints);

    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.h = 0;
    renderQuad.w = 0;

    for(int i = 0; i< numPoints; ++i)
    {
        linePoints[i].x = 0;
        linePoints[i].y = 0;
    }
}

/*****************************************************************************************************/

cPauseButton::cPauseButton(){}
cPauseButton::~cPauseButton(){free();}
void cPauseButton::free(){cSysButton::free();}
void cPauseButton::draw(SDL_Renderer * gRenderer)
{
    SDL_Rect renderQuad;

    renderQuad.x = cButton::position.x;
    renderQuad.y = cButton::position.y;
    renderQuad.h = cButton::buttonHeight;
    renderQuad.w = cButton::buttonWidth;

    int numQuads = 2;
    SDL_Rect pauseQuads[numQuads];

    pauseQuads[0].x = renderQuad.x;
    pauseQuads[0].y = renderQuad.y;
    pauseQuads[0].w = renderQuad.w / 3;
    pauseQuads[0].h = renderQuad.h;

    pauseQuads[1].x = renderQuad.x + 2 * (renderQuad.w / 3);
    pauseQuads[1].y = renderQuad.y;
    pauseQuads[1].w = renderQuad.w / 3;
    pauseQuads[1].h = renderQuad.h;

    if( cButton::buttonState == cButton::MOUSE_INSIDE)
    {
        SDL_SetRenderDrawColor(gRenderer , cSysButton::mSelectColor.r, cSysButton::mSelectColor.g, cSysButton::mSelectColor.b, cSysButton::mSelectColor.a );
    }
    else if( cButton::buttonState == cButton::MOUSE_OUTSIDE)
    {
        SDL_SetRenderDrawColor(gRenderer, cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a );
    }
    else if (cButton::buttonState == cButton::DEFAULT)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    else if( cButton::buttonState == cButton::BUTTON_MOUSE_DOWN)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mClickColor.r, cSysButton::mClickColor.g, cSysButton::mClickColor.b, cSysButton::mClickColor.a);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    SDL_RenderDrawRects(gRenderer, pauseQuads, 2);

    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.h = 0;
    renderQuad.w = 0;

    for(int i = 0; i< numQuads;++i)
    {
        pauseQuads[i].x = 0;
        pauseQuads[i].y = 0;
        pauseQuads[i].w = 0;
        pauseQuads[i].h = 0;
    }
}

/*****************************************************************************************************/

cNextSongButton::cNextSongButton(){}
cNextSongButton::~cNextSongButton(){ free(); }
void cNextSongButton::free(){ cSysButton::free(); }
void cNextSongButton::draw(SDL_Renderer * gRenderer)
{
    SDL_Rect renderQuad;

    renderQuad.x = cButton::position.x;
    renderQuad.y = cButton::position.y;
    renderQuad.h = cButton::buttonHeight;
    renderQuad.w = cButton::buttonWidth;

    int numPoints = 3;
    SDL_Point linePoints[numPoints];

    linePoints[0].x = renderQuad.x;
    linePoints[0].y = renderQuad.y + renderQuad.h;

    linePoints[1].x = renderQuad.x + renderQuad.w;
    linePoints[1].y = renderQuad.y + renderQuad.h /2;

    linePoints[2].x = renderQuad.x;
    linePoints[2].y = renderQuad.y;

    if( cButton::buttonState == cButton::MOUSE_INSIDE)
    {
        SDL_SetRenderDrawColor(gRenderer , cSysButton::mSelectColor.r, cSysButton::mSelectColor.g, cSysButton::mSelectColor.b, cSysButton::mSelectColor.a );
    }
    else if( cButton::buttonState == cButton::MOUSE_OUTSIDE)
    {
        SDL_SetRenderDrawColor(gRenderer, cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a );
    }
    else if (cButton::buttonState == cButton::DEFAULT)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    else if( cButton::buttonState == cButton::BUTTON_MOUSE_DOWN)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mClickColor.r, cSysButton::mClickColor.g, cSysButton::mClickColor.b, cSysButton::mClickColor.a);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    SDL_RenderDrawLines(gRenderer,linePoints,numPoints);

    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.h = 0;
    renderQuad.w = 0;

    for(int i = 0; i< numPoints; ++i)
    {
        linePoints[i].x = 0;
        linePoints[i].y = 0;
    }
}

/*****************************************************************************************************/

cPreviousSongButton::cPreviousSongButton(){}
cPreviousSongButton::~cPreviousSongButton(){ free();}
void cPreviousSongButton::free(){ cSysButton::free();}
void cPreviousSongButton::draw(SDL_Renderer * gRenderer)
{
    SDL_Rect renderQuad;

    renderQuad.x = cButton::position.x;
    renderQuad.y = cButton::position.y;
    renderQuad.h = cButton::buttonHeight;
    renderQuad.w = cButton::buttonWidth;

    int numPoints = 3;
    SDL_Point linePoints[numPoints];

    linePoints[0].x = renderQuad.x + renderQuad.w;
    linePoints[0].y = renderQuad.y;

    linePoints[1].x = renderQuad.x;
    linePoints[1].y = renderQuad.y + renderQuad.h /2 ;

    linePoints[2].x = renderQuad.x + renderQuad.w;
    linePoints[2].y = renderQuad.y + renderQuad.h;

    if( cButton::buttonState == cButton::MOUSE_INSIDE)
    {
        SDL_SetRenderDrawColor(gRenderer , cSysButton::mSelectColor.r, cSysButton::mSelectColor.g, cSysButton::mSelectColor.b, cSysButton::mSelectColor.a );
    }
    else if( cButton::buttonState == cButton::MOUSE_OUTSIDE)
    {
        SDL_SetRenderDrawColor(gRenderer, cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a );
    }
    else if (cButton::buttonState == cButton::DEFAULT)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    else if( cButton::buttonState == cButton::BUTTON_MOUSE_DOWN)
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mClickColor.r, cSysButton::mClickColor.g, cSysButton::mClickColor.b, cSysButton::mClickColor.a);
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer ,cSysButton::mColor.r, cSysButton::mColor.g, cSysButton::mColor.b, cSysButton::mColor.a);
    }
    SDL_RenderDrawLines(gRenderer,linePoints,numPoints);

    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.h = 0;
    renderQuad.w = 0;

    for(int i = 0; i< numPoints; ++i)
    {
        linePoints[i].x = 0;
        linePoints[i].y = 0;
    }
}

/*****************************************************************************************************/

cMediaPlayerButtons::cMediaPlayerButtons()
{
    SDL_Color color_black; SDL_Color color_yellow;
    color_black.a = 0;color_black.r = 0;color_black.g = 0;color_black.b = 0;
    color_yellow.a = 0;color_yellow.r = 255;color_yellow.g = 255;color_yellow.b = 0;

    buttonArr[STOP_BUTTON] = new cSysButton;
    buttonArr[PLAY_BUTTON] = new cPlayButton;
    buttonArr[PAUSE_BUTTON] = new cPauseButton;
    buttonArr[NEXT_BUTTON] = new cNextSongButton;
    buttonArr[PREVIOUS_BUTTON] = new cPreviousSongButton;

    for(int i = 0; i< MAX_BUTTONS; ++i)
    {
        buttonArr[i]->setDrawColors(color_black,color_yellow,color_black);
    }
}

cMediaPlayerButtons::~cMediaPlayerButtons(){ free();}

void cMediaPlayerButtons::free()
{
    for(int i = 0; i< MAX_BUTTONS; ++i)
    {
        buttonArr[i] = NULL;
    }
}

void cMediaPlayerButtons::setQuad(SDL_Rect * renderQuad)
{
    for(int i = 0; i < MAX_BUTTONS; ++i)
    {
        if(i != 0){ renderQuad->x = renderQuad->x + renderQuad->w + 10;}
        buttonArr[i]->setQuad(renderQuad);
    }
}

void cMediaPlayerButtons::handleEvent(SDL_Event *e)
{
    for(int i = 0; i< MAX_BUTTONS; ++i)
    {
        buttonArr[i]->handleEvent(e);
    }
}
void cMediaPlayerButtons::draw(SDL_Renderer * gRenderer)
{
    for(int i = 0; i < MAX_BUTTONS; ++i)
    {
        buttonArr[i]->draw(gRenderer);
    }
}

int cMediaPlayerButtons::onClick()
{
    for(int i = 0; i< MAX_BUTTONS; ++i)
    {
        if(buttonArr[i]->onClick())
        {
            return i;
        }
    }
    return -1;
}

/***********************************************************************************************/

cMediaPlayer::cMediaPlayer(){};
cMediaPlayer::~cMediaPlayer(){};

void cMediaPlayer::free()
{
    mediaPlayerButtons.free();
    curentSelection = 0;
    background.free();
    mFont = NULL;
    for(int i = 0; i < MAX_SONGS ; ++i)
    {
        Mix_FreeMusic(songMusic[i]);
        songButton[i].free();
        songLable[i][cTexturedButton::CLICK_TEXTURE].free();
        songLable[i][cTexturedButton::OUTSIDE_TEXTURE].free();
        songLable[i][cTexturedButton::INSIDE_TEXTURE].free();
    }
    emptyLable[cTexturedButton::CLICK_TEXTURE].free();
    emptyLable[cTexturedButton::OUTSIDE_TEXTURE].free();
    emptyLable[cTexturedButton::INSIDE_TEXTURE].free();
}

bool cMediaPlayer::loadMedia(SDL_Renderer * gRenderer)
{
    if(!background.loadTextureFromFile("media/background.png", gRenderer, NULL))
    {
        printf("Unable to load background Texture: SDL_ERROR: %s \n", SDL_GetError());
        return false;
    }

    SDL_Rect mediaPlayerButtonsQuad;
    mediaPlayerButtonsQuad.x = 10;
    mediaPlayerButtonsQuad.y = 580;
    mediaPlayerButtonsQuad.w = 90;
    mediaPlayerButtonsQuad.h = 80;

    mediaPlayerButtons.setQuad(&mediaPlayerButtonsQuad);

    mFont = TTF_OpenFont("media/times.ttf", 20);
    if(mFont == NULL)
    {
        printf("Error loading font: SDL_ERROR: %s \n", SDL_GetError());
        return false;
    }

    yellowHighlight.a = 50;
    yellowHighlight.r = 255;
    yellowHighlight.g = 255;
    yellowHighlight.b = 0;

    color_black.a = 0;
    color_black.r = 0;
    color_black.g = 0;
    color_black.b = 0;

    highLightQuad.x = 70;
    highLightQuad.y = 40;
    highLightQuad.w = 394;
    highLightQuad.h = 45;

    emptyLable[cTexturedButton::CLICK_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&yellowHighlight,"Empty");
    emptyLable[cTexturedButton::OUTSIDE_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_black,"Empty");
    emptyLable[cTexturedButton::INSIDE_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_black,"Empty");

    for(int i = 0; i < MAX_SONGS; ++i)
    {
        songButton[i].setTexture(emptyLable);
        if(i != 0){ songButton[i].setPosition(90,45 * (i+1)); }
        else { songButton[i].setPosition(90,45); }
    }

    curentSelection = 0;

    FILE *playList = fopen("playlist.txt","r");
    if (playList == NULL)
    {
        printf("Can not find playlist.txt! \n");
        return false;
    }
    char fileBuff[255]; int i = 0;
    for(int i = 0; i < MAX_SONGS ; ++i){songMusic[i] = NULL;}
    while(fscanf(playList,"%[^\n]\n", fileBuff) != EOF && i < MAX_SONGS)
    {
        songLable[i][cTexturedButton::CLICK_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&yellowHighlight,fileBuff);
        songLable[i][cTexturedButton::OUTSIDE_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_black,fileBuff);
        songLable[i][cTexturedButton::INSIDE_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_black,fileBuff);
        songButton[i].setTexture(songLable[i]);

        songMusic[i] = Mix_LoadMUS(fileBuff);
        if(songMusic[i] == NULL)
        {
            printf("Error loading file %s", fileBuff);
            printf(" : MIX_ERROR: %s \n", Mix_GetError());
            return false;
        }

        ++i;
    }
    fclose(playList);
    playList = NULL;
    for(int i = 0; i < 255; ++i)
    {
        fileBuff[i] = (char)NULL;
    }

    return true;
}

void cMediaPlayer::handleEvent(SDL_Event * e)
{
    mediaPlayerButtons.handleEvent(e);

    if(curentSelection == MAX_SONGS) { curentSelection = 0;}
    else if(curentSelection == -1 ){ curentSelection = MAX_SONGS - 1;}

    for(int i = 0; i< MAX_SONGS; ++i)
    {
        highLightQuad.y = songButton[curentSelection].getPosition().y;
    }

    for(int i = 0; i < MAX_SONGS; ++i)
    {
        songButton[i].handleEvent(e);
        if(songButton[i].onClick())
        {
            Mix_HaltMusic();
            Mix_PlayMusic(songMusic[i], -1 );
            highLightQuad.y = songButton[i].getPosition().y;
            curentSelection = i;
        }
    }

    switch (mediaPlayerButtons.onClick())
    {
        case cMediaPlayerButtons::NEXT_BUTTON:
            curentSelection += 1;
            Mix_HaltMusic();
            Mix_PlayMusic(songMusic[curentSelection], -1 );
            break;
        case cMediaPlayerButtons::PREVIOUS_BUTTON:
            curentSelection -=1;
            Mix_HaltMusic();
            Mix_PlayMusic(songMusic[curentSelection], -1 );
            break;
        case cMediaPlayerButtons::PLAY_BUTTON:
            Mix_HaltMusic();
            Mix_PlayMusic(songMusic[curentSelection], -1 );
            break;
        case cMediaPlayerButtons::PAUSE_BUTTON:
            if( Mix_PausedMusic() == 1 ){ Mix_ResumeMusic(); }
            else { Mix_PauseMusic(); }
            break;
        case cMediaPlayerButtons::STOP_BUTTON:
            Mix_HaltMusic();
            break;
        case -1:
            break;
        default:
            break;
    }
}

void cMediaPlayer::render(SDL_Renderer * gRenderer)
{
    background.render(gRenderer,NULL,0,0,NULL,SDL_FLIP_NONE,0,0);

    SDL_SetRenderDrawColor(gRenderer,yellowHighlight.r,yellowHighlight.g,yellowHighlight.b, yellowHighlight.a);
    SDL_RenderFillRect(gRenderer,&highLightQuad);

    mediaPlayerButtons.draw(gRenderer);

    for(int i = 0; i < MAX_SONGS; ++i)
    {
        songButton[i].render(gRenderer);
    }
}

/******************************************************************************************************************/
