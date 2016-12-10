#include "cObject.h"

cObject::cObject(){ free(); }

cObject::~cObject(){ free(); }

void cObject::free()
{
    if(&spriteTexture == NULL)
    {
       spriteTexture->free();
    }
    position.x = 0;
    position.y = 0;
    spriteTexture = NULL;
}

bool cObject::setTexture(cTexture* mTexture)
{
    free();
    spriteTexture = mTexture;
    if(spriteTexture != NULL){ return true;}
    else
    {
        printf("Error setting texture in cObject: SDL_ERROR:%s \n", SDL_GetError());
        free();
        return false;
    }
}

void cObject::renderTexture(SDL_Renderer* gRenderer)
{
    if(spriteTexture != NULL)
    {
        spriteTexture->render(gRenderer,NULL,0,0,NULL,SDL_FLIP_NONE, position.x, position.y);
    }
    else
    {
        printf("Error rendering Texture: SDL_ERROR: %s \n", SDL_GetError());
    }
}

SDL_Point cObject::getPosition(){ return position; }

void cObject::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void cObject::setMotionState(int motionState, float increment)
{
    if(motionState == OBJECT_STATE::MOVING){
        motionState = OBJECT_STATE::STOP;
    }
    switch(motionState)
    {
        case OBJECT_STATE::STOP:
            position.x = position.x;
            position.y = position.y;
            break;

        case OBJECT_STATE::MOVE_S:
            position.y += increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_S;
            break;

        case OBJECT_STATE::MOVE_N:
            position.y -= increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_N;
            break;

        case OBJECT_STATE::MOVE_E:
            position.x += increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_E;
            break;

        case OBJECT_STATE::MOVE_W:
            position.x -= increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_W;
            break;

        case OBJECT_STATE::MOVE_NE:
            position.y -= increment;
            position.x += increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_NE;
            break;

        case OBJECT_STATE::MOVE_NW:
            position.y -= increment;
            position.x -= increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_NW;
            break;

        case OBJECT_STATE::MOVE_SE:
            position.y += increment;
            position.x += increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_SE;
            break;

        case OBJECT_STATE::MOVE_SW:
            position.y += increment;
            position.x -= increment;
            motionState = OBJECT_STATE::MOVING;
            CurrentMotionState = OBJECT_STATE::MOVE_SW;
            break;
        default:
            motionState = OBJECT_STATE::STOP;
            CurrentMotionState = OBJECT_STATE::DEFAULT;
            break;
    }
}

int cObject::getMotionState(){ return CurrentMotionState;}
SDL_Rect cObject::getTextureQuad(){ return spriteTexture->getQuad();}
