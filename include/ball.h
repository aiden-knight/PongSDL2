#pragma once
#include <SDL2/SDL.h>

#include <vector.h>
#include <gameDataStruct.h>

class Ball
{
  private:
    SDL_Rect mRect;
    int mVelocity;
    Vector2 mDirection;
    Vector2 mPosition;
    
    void posToRect();
    bool checkIntersect(SDL_Rect& collider);
    bool checkCollision(SDL_Rect& collider);
    void changeDirection(SDL_Rect& hitCollider);
    void reset(int screenWidth, int screenHeight, int direction);
  public:
    Ball(int xPos, int yPos);
    const SDL_Rect& getCollider() const;
    void updatePos(GameData& gameData);
};