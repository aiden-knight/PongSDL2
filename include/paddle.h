#pragma once
#include <SDL2/SDL.h>

class Paddle
{
    private:
        SDL_Rect mRect;
        float mPosY;
    public:
        Paddle(int xPos, int yPos);
        const SDL_Rect& getCollider() const;
        bool updateYPos(float distance, int maxY);
};