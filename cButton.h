/*************************************************
cButton.h
@: Nathaniel Dielen
D: 11-22-16

A Button class

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

*************************************************/
#ifndef cButton_h
#define cButton_h

#include "stdafx.h"
#include "cObject.h"

/*************************************************
* cButton mButton                                *
*                                                *
* mButton.handleEvent(&e);                       *
*                                                *
* if(mButton.onClick()){ ..do stuff }            *
**************************************************/
class cButton : public cObject
{
    public:
        cButton(); ~cButton();
        virtual void free();

        enum {DEFAULT = 0, BUTTON_MOUSE_DOWN, BUTTON_MOUSE_UP, MOUSE_INSIDE, MOUSE_OUTSIDE, TOTAL};

        void handleEvent(SDL_Event* e);

        bool onClick();

    protected:

        int buttonState; int buttonWidth; int buttonHeight; bool isClicked;
};

/****************************************************************************
* cSysButton mButton
*
*    SDL_Rect setQuad;
*    setQuad.x = 50;
*    setQuad.y = 100;
*    setQuad.h = 100;
*    setQuad.w = 100;
*    mButton.setQuad(&setQuad);
*
*    SDL_Color color_black;
*    color_black.a = 0;
*    color_black.r = 0;
*    color_black.g = 0;
*    color_black.b = 0;
*
*    SDL_Color color_yellow;
*    color_yellow.a = 0;
*    color_yellow.r = 255;
*    color_yellow.g = 255;
*    color_yellow.b = 0;
*
*    mButton.setDrawColors(color_black, color_yellow, color_yellow);
*
*    mButton.draw(gRenderer);
*
************************************************************************/
class cSysButton : public cButton
{
    public:
        cSysButton(); ~cSysButton();
        virtual void free();

        void setQuad(SDL_Rect* renderQuad);

        void setDrawColors(SDL_Color  color , SDL_Color selectColor, SDL_Color clickColor);

        virtual void draw(SDL_Renderer* gRenderer);

    protected:

        SDL_Color mColor; SDL_Color mSelectColor; SDL_Color mClickColor;
};

/***********************************************************************************
* cSysTickButton mButton
*
*   if(mButton.isSelected()){ ...do stuff }
*
***********************************************************************************/
class cSysTickButton : public cSysButton
{
    public:
        cSysTickButton(); ~cSysTickButton();
        void free();

        void draw(SDL_Renderer * gRenderer);
        void handleEvent(SDL_Event * e);
        bool isSelected();

    private:
        bool select;
};

/*****************************************************************************************************
* cTexturedButton mTbutton
* cTexture buttonTexture;
*
*   if(!buttonTexture.loadTextureFromFile("media/button.png",gRenderer,NULL)){printf("error!!\n");}
*
*   SDL_Rect clip[cTexturedButton::TOTAL_TEXTURE];
*
*   clip[cTexturedButton::OUTSIDE_TEXTURE].x = buttonTexture.getQuad().x;
*   clip[cTexturedButton::OUTSIDE_TEXTURE].y = buttonTexture.getQuad().y;
*   clip[cTexturedButton::OUTSIDE_TEXTURE].w = buttonTexture.getQuad().w;
*   clip[cTexturedButton::OUTSIDE_TEXTURE].h = buttonTexture.getQuad().h /2;
*
*   clip[cTexturedButton::INSIDE_TEXTURE].x = buttonTexture.getQuad().x;
*   clip[cTexturedButton::INSIDE_TEXTURE].y = buttonTexture.getQuad().y;
*   clip[cTexturedButton::INSIDE_TEXTURE].w = buttonTexture.getQuad().w;
*   clip[cTexturedButton::INSIDE_TEXTURE].h = buttonTexture.getQuad().h /2;
*
*   clip[cTexturedButton::CLICK_TEXTURE].x = buttonTexture.getQuad().x;
*   clip[cTexturedButton::CLICK_TEXTURE].y = buttonTexture.getQuad().y + buttonTexture.getQuad().h /2;
*   clip[cTexturedButton::CLICK_TEXTURE].w = buttonTexture.getQuad().w;
*   clip[cTexturedButton::CLICK_TEXTURE].h = buttonTexture.getQuad().h /2;
*
*   mTbutton.setTexture(&buttonTexture, clip);
*
*   mTbutton.render(gRenderer);
*******************************************************************************************************/
class cTexturedButton : public cButton
{
    public:
        cTexturedButton(); ~cTexturedButton();
        void free();
        void handleEvent(SDL_Event * e);

        enum {OUTSIDE_TEXTURE = 0, INSIDE_TEXTURE, CLICK_TEXTURE, TOTAL_TEXTURE};
        void setTexture(cTexture * mTexture, SDL_Rect mClip[TOTAL_TEXTURE]);
        void render(SDL_Renderer * gRenderer);

    protected:
        SDL_Rect clip[TOTAL_TEXTURE]; SDL_Rect * currentRect;
};
/***********************************************************************************
* cTexturedTickButton mButton
*
*   if(mButton.isSelected()){ ...do stuff }
*
***********************************************************************************/
class cTexturedTickButton : public cTexturedButton
{
    public:
        cTexturedTickButton(); ~cTexturedTickButton();
        void free();
        void handleEvent(SDL_Event *e);
        bool isSelected();

    private:
        bool select;
};
/************************************************************************************
*  TTF_Font * mFont;
*  cTexturedTextButton mButton;
*  cTexture buttonTextures[cTexturedButton::TOTAL_TEXTURE];
*
*    SDL_Color color_black;
*    color_black.a = 0;
*    color_black.r = 0;
*    color_black.g = 0;
*    color_black.b = 0;
*
*    SDL_Color color_yellow;
*    color_yellow.a = 0;
*    color_yellow.r = 255;
*    color_yellow.g = 255;
*    color_yellow.b = 0;
*
*    mFont = TTF_OpenFont("media/times.ttf", 50);
*
*    buttonTextures[cTexturedTextButton::OUTSIDE_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_black,"Test");
*    buttonTextures[cTexturedTextButton::INSIDE_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_yellow,"Test");
*    buttonTextures[cTexturedTextButton::CLICK_TEXTURE].loadFontTextureFromFile(gRenderer,mFont,&color_yellow,"Test");
*
*    mButton.setTexture(buttonTextures);
*
*    mButton.setPosition(50,50);
*
*        mButton.handleEvent(&e);
*        if(mButton.onClick()){printf("clicked!");}
*
*        mButton.render(gRenderer);
*
***************************************************************************************************************************/
class cTexturedTextButton : public cButton
{
    public:
        cTexturedTextButton(); ~cTexturedTextButton();
        void free();
        enum {OUTSIDE_TEXTURE = 0, INSIDE_TEXTURE, CLICK_TEXTURE, TOTAL_TEXTURE};

        void setTexture(cTexture mTexture[TOTAL_TEXTURE]);
        void handleEvent(SDL_Event * e);
        void render(SDL_Renderer * gRenderer);

    private:
        cTexture * textureArr[TOTAL_TEXTURE]; cTexture * currentTexture;
};

#endif // cButton_h
