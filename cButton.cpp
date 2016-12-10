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
#include "cButton.h"

cButton::cButton()
{
    buttonState = DEFAULT;
    buttonWidth = 0; buttonHeight = 0;
    isClicked = false;
}

cButton::~cButton(){free();}

void cButton::free()
{
    buttonState = DEFAULT;
    buttonWidth = 0; buttonHeight = 0;
    isClicked = false;
    cObject::free();
}

void cButton::handleEvent(SDL_Event *e)
{
   //If mouse event occurs
   if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
   {

        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x,&y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse left of button
        if(x < position.x) { inside = false; }
        //Mouse is right of button
        else if( x > position.x + buttonWidth ) { inside = false; }
        //Mouse above button
        else if ( y < position.y){ inside = false; }
        //Mouse below button
        else if (y > position.y + buttonHeight){ inside = false;}

        //Mouse outside button
        if (!inside){ buttonState = MOUSE_OUTSIDE;}
        //Mouse inside button
        else if(inside)
        {
            switch( e->type)
            {
                case SDL_MOUSEMOTION:
                    buttonState = MOUSE_INSIDE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    buttonState = BUTTON_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    buttonState = BUTTON_MOUSE_UP;
                    break;
                default:
                    break;
            }
        }
        if(buttonState == BUTTON_MOUSE_DOWN){ isClicked = true; }
        else {isClicked = false;}
   }
}

bool cButton::onClick(){ return isClicked; }

/***************************************************************************/

cSysButton::cSysButton()
{
    mColor.r = 0; mColor.g = 0; mColor.b = 0; mColor.a = 0;
    mSelectColor.r = 0; mSelectColor.g = 0; mSelectColor.b = 0; mSelectColor.a = 0;
    mClickColor.r = 0; mClickColor.g = 0; mClickColor.b = 0; mClickColor.a = 0;
}

cSysButton::~cSysButton(){ free();}

void cSysButton::free()
{
    cButton::free();
    mColor.r = 0; mColor.g = 0; mColor.b = 0; mColor.a = 0;
    mSelectColor.r = 0; mSelectColor.g = 0; mSelectColor.b = 0; mSelectColor.a = 0;
    mClickColor.r = 0; mClickColor.g = 0; mClickColor.b = 0; mClickColor.a = 0;
}

void cSysButton::draw(SDL_Renderer * gRenderer)
{

    SDL_Rect renderQuad;

    renderQuad.x = cButton::position.x;
    renderQuad.y = cButton::position.y;
    renderQuad.h = cButton::buttonHeight;
    renderQuad.w = cButton::buttonWidth;

    if( cButton::buttonState == cButton::MOUSE_INSIDE)
    {
           SDL_SetRenderDrawColor(gRenderer , mSelectColor.r, mSelectColor.g, mSelectColor.b, mSelectColor.a );
    }
    else if( cButton::buttonState == cButton::MOUSE_OUTSIDE)
    {
         SDL_SetRenderDrawColor(gRenderer, mColor.r, mColor.g, mColor.b, mColor.a );
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer ,mColor.r, mColor.g, mColor.b, mColor.a);
    }

    SDL_RenderDrawRect(gRenderer, &renderQuad);

    if( cButton::buttonState == cButton::BUTTON_MOUSE_DOWN)
    {
        SDL_SetRenderDrawColor(gRenderer ,mClickColor.r, mClickColor.g, mClickColor.b, mClickColor.a);
        SDL_RenderFillRect(gRenderer, &renderQuad);
    }

    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.h = 0;
    renderQuad.w = 0;
}

void cSysButton::setQuad(SDL_Rect * renderQuad)
{
    cButton::setPosition(renderQuad->x,renderQuad->y);
    cButton::buttonHeight = renderQuad->h;
    cButton::buttonWidth = renderQuad->w;

}

void cSysButton::setDrawColors(SDL_Color color , SDL_Color selectColor, SDL_Color clickColor)
{
    mColor = color;
    mSelectColor = selectColor;
    mClickColor = clickColor;
}
/******************************************************************************************************************/

cSysTickButton::cSysTickButton(){ select = false;}
cSysTickButton::~cSysTickButton(){ free();}

void cSysTickButton::free()
{
    cSysButton::free();
    select = false;
}

bool cSysTickButton::isSelected()
{
    return select;
}

void cSysTickButton::handleEvent(SDL_Event * e)
{
    cSysButton::handleEvent(e);
    if(cButton::onClick() == true)
    {
        if(select){ select = false ;}
        else { select = true;}
    }
}

void cSysTickButton::draw(SDL_Renderer * gRenderer)
{
    cSysButton::draw(gRenderer);

    SDL_Rect renderQuad;

    renderQuad.x = cButton::position.x;
    renderQuad.y = cButton::position.y;
    renderQuad.h = cButton::buttonHeight;
    renderQuad.w = cButton::buttonWidth;

    if(isSelected())
    {
        SDL_SetRenderDrawColor(gRenderer , cSysButton::mSelectColor.r, cSysButton::mSelectColor.g, cSysButton::mSelectColor.b, cSysButton::mSelectColor.a );
        SDL_RenderFillRect(gRenderer, &renderQuad);
    }

    renderQuad.x = 0;
    renderQuad.y = 0;
    renderQuad.h = 0;
    renderQuad.w = 0;

}
/*************************************************************************************************************************************************************/

cTexturedButton::cTexturedButton()
{
    for(int i = 0; i< TOTAL_TEXTURE; ++i)
    {
        clip[i].x = 0;
        clip[i].y = 0;
        clip[i].w = 0;
        clip[i].h = 0;
    }
    currentRect = NULL;
}
cTexturedButton::~cTexturedButton(){ free(); }

void cTexturedButton::free()
{
    cButton::free();
    for(int i = 0; i< TOTAL_TEXTURE; ++i)
    {
        clip[i].x = 0;
        clip[i].y = 0;
        clip[i].w = 0;
        clip[i].h = 0;
    }
    currentRect = NULL;
}

void cTexturedButton::setTexture(cTexture * mTexture,SDL_Rect mClip[TOTAL_TEXTURE])
{
    cButton::setTexture(mTexture);
    for(int i = 0; i< TOTAL_TEXTURE; ++i)
    {
        clip[i] = mClip[i];
    }
}

void cTexturedButton::handleEvent(SDL_Event * e)
{
    cButton::handleEvent(e);

    currentRect = NULL;

    if(cButton::buttonState == cButton::MOUSE_INSIDE ){ currentRect = &clip[INSIDE_TEXTURE]; }
    else if(cButton::buttonState == cButton::MOUSE_OUTSIDE){ currentRect = &clip[OUTSIDE_TEXTURE];}
    else if(cButton::buttonState == cButton::BUTTON_MOUSE_DOWN){ currentRect = &clip[CLICK_TEXTURE];}
    else { currentRect = &clip[OUTSIDE_TEXTURE];}

    cButton::buttonHeight = currentRect->h;
    cButton::buttonWidth = currentRect->w;
}

void cTexturedButton::render(SDL_Renderer * gRenderer)
{
    cButton::spriteTexture->render(gRenderer,currentRect,0,0,0,SDL_FLIP_NONE,cButton::position.x,cButton::position.y);
}

/**************************************************************************************************************************************/

cTexturedTickButton::cTexturedTickButton(){ select = false;}
cTexturedTickButton::~cTexturedTickButton(){ free();}

void cTexturedTickButton::free()
{
    cTexturedButton::free();
    select = false;
}

bool cTexturedTickButton::isSelected(){ return select;}

void cTexturedTickButton::handleEvent(SDL_Event *e)
{
    cTexturedButton::handleEvent(e);

    if(cTexturedButton::onClick() == true)
    {
        if(select){ select = false ;}
        else { select = true;}
    }

    if(isSelected()){ cTexturedButton::currentRect = &cTexturedButton::clip[cTexturedButton::CLICK_TEXTURE]; }
}

/******************************************************************************************************************************************/

cTexturedTextButton::cTexturedTextButton()
{
    for(int i = 0; i< TOTAL_TEXTURE; ++i)
    {
        textureArr[i] = NULL;
    }
    currentTexture = NULL;

}
cTexturedTextButton::~cTexturedTextButton(){ free(); }

void cTexturedTextButton::free()
{
    cButton::free();
    for(int i = 0; i< TOTAL_TEXTURE; ++i)
    {
        textureArr[i] = NULL;
    }
    currentTexture = NULL;
}

void cTexturedTextButton::setTexture(cTexture mTexture[TOTAL_TEXTURE])
{
    for(int i = 0; i< TOTAL_TEXTURE; ++i)
    {
        textureArr[i] = &mTexture[i];
    }
}

void cTexturedTextButton::handleEvent(SDL_Event * e)
{
    cButton::handleEvent(e);

    currentTexture = NULL;

    if(cButton::buttonState == cButton::MOUSE_INSIDE ){ currentTexture = textureArr[INSIDE_TEXTURE]; }
    else if(cButton::buttonState == cButton::MOUSE_OUTSIDE){ currentTexture = textureArr[OUTSIDE_TEXTURE];}
    else if(cButton::buttonState == cButton::BUTTON_MOUSE_DOWN){ currentTexture = textureArr[CLICK_TEXTURE];}
    else { currentTexture = textureArr[OUTSIDE_TEXTURE];}

    cButton::buttonWidth = currentTexture->getQuad().w;
    cButton::buttonHeight = currentTexture->getQuad().h;
}

void cTexturedTextButton::render(SDL_Renderer * gRenderer)
{
    currentTexture->render(gRenderer,0,0,0,NULL,SDL_FLIP_NONE,cButton::position.x,cButton::position.y);
}
