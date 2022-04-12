#pragma once
#include <SDL2/SDL.h>

class Paddle
{
    private:
        SDL_Rect mRect;
        float mPosY;
    public:
        Paddle(int xPos, int yPos);
        SDL_Rect getCollider();
        bool updateYPos(float distance, int maxY);
};