#include <SDL2/SDL.h>
#include <math.h>

#include <paddle.h>

Paddle::Paddle(int xPos, int yPos)
{
    mRect = {xPos, yPos, 10, 50};
    mPosY = yPos;
}

SDL_Rect Paddle::getCollider()
{
    return mRect;
}

// Updates Y position then returns whether it hit edge of screen or not
bool Paddle::updateYPos(float distance, int maxY)
{
    bool hitEdge = false;

    mPosY += distance;
    if(mPosY < 0)
    {
        mPosY = 0;
        hitEdge = true;
    }
    else if(mPosY > maxY-mRect.h)
    {
        mPosY = maxY-mRect.h;
        hitEdge = true;
    }

    mRect.y = round(mPosY);
    return hitEdge;
}