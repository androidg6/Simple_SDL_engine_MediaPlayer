/*********************************************************************************
cObject.h
@:Nathaniel Dielen
D:11-9-16

An object controller class.

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
#ifndef cObject_h
#define cObject_h
/*********************************************************************************/
#include "stdafx.h"
#include "cTexture.h"
/*********************************************************************************
cObject usage:

cObject mObject;
cObject mObject[arraySize];
**********************************************************************************/
class cObject
{
    public:
        cObject(); ~cObject();
        /**************************************************************************
        * Deallocate everything
        **************************************************************************/
        void free();
        /*************************************************************************/
        bool setTexture(cTexture* mTexture);
        /*************************************************************************
        * Set the Texture
        *
        * cTexture mTexture;
        * mTexture.loadTextureFromFile("media/logos.bmp", gRenderer,NULL);
        *
        * cObject mObject;
        * mObject.setTexture(&mTexture);
        *
        **************************************************************************/
        void renderTexture(SDL_Renderer* gRenderer);
        /*************************************************************************
        * Render the Texture
        *
        * mObject.renderTexture(gRenderer);
        *
        *************************************************************************/
        SDL_Point getPosition(); void setPosition(int x ,int y);
        /************************************************************************
        * Get the Object Position and Set the Object Position
        *
        * mObject.setPosition(posX,posY);
        *
        * mObject.getPosition().x;
        * mObject.getPosition().y;
        *
        ************************************************************************/
        void setMotionState(int motionState, float increment); int getMotionState();
        /***********************************************************************
        * Add motion to Object
        *
        * mObject.setMotionState(OBJECT_STATE::motionStateFlag, speed);
        *
        ***********************************************************************/
        SDL_Rect getTextureQuad();
        /***********************************************************************
        * Get the texture's renderQuad..
        ***********************************************************************/
    protected:
        cTexture* spriteTexture; SDL_Point position;
    private:
        int CurrentMotionState;
};

class OBJECT_STATE
{
    public:
        enum {DEFAULT,MOVE_N,MOVE_NE,MOVE_E,
              MOVE_SE,MOVE_S,MOVE_SW,MOVE_W,
              MOVE_NW,MOVE_CUSTOM,STOP,MOVING,
              ALIVE, DEAD};
};
#endif // cObject_h
