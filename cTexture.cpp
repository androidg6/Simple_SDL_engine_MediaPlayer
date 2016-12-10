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

#include "cTexture.h"

cTexture::cTexture()
{
    gTexture = NULL;
    isLocked = true;
    renderQuad.h = 0;
    renderQuad.w = 0;
    renderQuad.x = 0;
    renderQuad.y = 0;
}
cTexture::~cTexture()
{
    free();
}

bool cTexture::loadTextureFromFile(std::string path, SDL_Renderer* gRenderer, SDL_Color* colorKey)
{
    free();
    //Load image at a specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());

    if( loadedSurface == NULL)
    {
        printf("Unable to load image %s! IMG_Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    //Convert the surface
    else
    {
        if( colorKey != NULL)
        {
            //Color key image
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, colorKey->r, colorKey->g, colorKey->b ) );
        }
        //Create new texture from surface pixels
        gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface );
        if( gTexture == NULL )
        {
            printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }
        else
        {
            renderQuad.w = loadedSurface->w;
            renderQuad.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}

void cTexture::render(SDL_Renderer* gRenderer, SDL_Rect* clip,
                      int zoom,double angle, SDL_Point* center,
                      SDL_RendererFlip flip, int posX, int posY)
{
    if( clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    renderQuad.w += zoom;
    renderQuad.h += zoom;

    renderQuad.x  = posX;
    renderQuad.y = posY;

    SDL_RenderCopyEx(gRenderer, gTexture , clip, &renderQuad,angle,center,flip);
}

void cTexture::free()
{
    if( gTexture != NULL)
    {
        renderQuad.h = 0;
        renderQuad.w = 0;
        renderQuad.x = 0;
        renderQuad.y = 0;

        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
    }
}

void cTexture::modulateTexture(SDL_Color* modColor, SDL_BlendMode blendMode)
{
    if(gTexture != NULL )
    {
        //Modulate texture
        SDL_SetTextureColorMod( gTexture, modColor->r, modColor->g, modColor->b );

        if( blendMode != SDL_BLENDMODE_NONE)
        {

            //Set blending function
            SDL_SetTextureBlendMode(gTexture, blendMode);

            //Modulate texture alpha
            SDL_SetTextureAlphaMod( gTexture, modColor->a );
        }
    }
}
#ifdef _SDL_TTF_H
bool cTexture::loadFontTextureFromFile(SDL_Renderer *gRenderer, TTF_Font* mFont,SDL_Color* color, std::string fontText)
{
    free();
    if(mFont == NULL)
    {
        printf("Error loading font: SDL_TTF ERROR: %s \n", TTF_GetError());
        return false;
    }
    else
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, fontText.c_str(), *color);
        if(textSurface == NULL)
        {
                printf("Error rendering text: SDL_TTF ERROR: %s \n", TTF_GetError());
                return false;
        }
        else
        {
            gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            if(gTexture == NULL)
            {
                printf("Error creating texture from surface: SDL ERROR: %s", SDL_GetError());
            }
            else
            {
                renderQuad.w = textSurface->w;
                renderQuad.h = textSurface->h;
            }
        }
        SDL_FreeSurface(textSurface);
        textSurface = NULL;
    }
    return true;

}
#endif // _SDL_TTF_H

void cTexture::lock(){ isLocked = true;}
void cTexture::unlock(){ isLocked = false;}
SDL_Rect cTexture::getQuad(){ return renderQuad;}
