/*********************************************************************************
cTexture.h
@:Nathaniel Dielen
D:11-9-16

A Texture controller class.

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
#ifndef  cTexture_h
#define cTexture_h
#include "stdafx.h"
/*********************************************************************************
cTexture usage:

cTexture mTexture;
cTexture mTexture[arraySize];
**********************************************************************************/
class cTexture
{
    public:
        cTexture(); ~cTexture();
        /**********************************************************************/
        void free();
        /*****************************************************************************************
        * Deallocate everything.
        ******************************************************************************************/
        bool loadTextureFromFile(std::string path, SDL_Renderer* gRenderer , SDL_Color* colorKey);
        /*****************************************************************************************
        * Load a Texture with colorKey. Returns false on error;
        * cTexture mTexture;
        *
        * SDL_Color colorKey;
        * colorKey.r = someValue;
        * colorKey.g = someValue;
        * colorKey.b = someValue;
        * colorKey.a = someValue;
        *
        * mTexture.loadTextureFromFile("path/to/file.fileType", Renderer, &colorKey);
        *****************************************************************************************/
        void render(SDL_Renderer* gRenderer, SDL_Rect* clip,int zoom,
                    double angle, SDL_Point* center,
                    SDL_RendererFlip flip, int posX, int posY);
        /*****************************************************************************************
        *  Render Texture to screen.
        *
        *  cTexture mTexture
        *
        *  // A clip of the surface that is to be rendered
        *  SDL_Rect clip;
        *  clip.x = someValue;
        *  clip.y = someValue;
        *  clip.w = someValue;
        *  clip.h = someValue;
        *
        *
        *  //Point of Rotation
        *  SDL_Point center;
        *  center.x = someValue;
        *  center.y = someValue;
        *
        *  // Degree at which to rotate
        *  double angle = someValue;
        *
        *  //Amount to increase size of texture
        *  int zoom = someValue;
        *
        *  //Which way to flip the texture
        *  SDL_RedererFlip flip = { SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL }
        *
        *  //Position on the screen/window
        *  int posX = someValue; int posY = someValue;
        *
        *
        *  mTexture.render(gRenderer,&clip,zoom,angle,center,flip,posX,posY);
        *
        *  ... or ..
        *
        *  mTexture.render(gRenderer,NULL,0,0,NULL,SDL_FLIP_NONE, 0, 0);
        *
        *  note: Zoom only works if rendering a clip!
        *
        **************************************************************************************/
        void modulateTexture(SDL_Color* modColor, SDL_BlendMode blendMode);
        /*************************************************************************************
        * Modulate the texture color.
        *
        * cTexture mTexture;
        *
        * SDL_Color modColor;
        * modColor.r = someValue;
        * modColor.g = someValue;
        * modColor.b = someValue;
        * modColor.a = someValue;
        *
        * SDL_BlendMode blendMode = { SDL_BLENDMODE_NONE | SDL_BLENDMODE_MOD |
        *                             SDL_BLENDMODE_ADD | SDL_BLENDMODE_BLEND }
        *
        *
        * mTexture.modulateTexture(&modColor, SDL_BLENDMODE_BLEND);
        *
        ***************************************************************************************/
        #ifdef _SDL_TTF_H
        bool loadFontTextureFromFile(SDL_Renderer *gRenderer, TTF_Font* mFont,SDL_Color* color, std::string fontText);
        #endif // _SDL_TTF_H
        /***************************************************************************************
        * Load a Font from a file and render some text from the font
        *
        *  cTexture mTexture;
        *
        *  mTexture.loadFontTextureFromFile(renderer, TTF_OpenFont("path/to/file.ttf", fontSize),
        *                                   &color, "Text to be rendered");
        *
        *****************************************************************************************/
        void lock(); void unlock();
        /****************************************************************************************
        * Lock and unlock texture
        *****************************************************************************************/
        SDL_Rect getQuad();
        /*****************************************************************************************
        * Get the render Quad
        ******************************************************************************************/

    private:
        SDL_Texture* gTexture; SDL_Rect renderQuad; bool isLocked;
};

#endif // cTexture_h
