#pragma once
#include <SDL2/SDL.h>

#include <vector.h>

class Ball
{
  private:
    SDL_Rect mRect;
    int mVelocity;
    Vector2 mDirection;
    Vector2 mPosition;
  public:
    Ball(int xPos, int yPos);
    void posToRect();
    SDL_Rect getCollider();
    bool checkCollision(SDL_Rect collider);
    void updatePos(SDL_Rect collider1, SDL_Rect collider2, float timeStep);
};