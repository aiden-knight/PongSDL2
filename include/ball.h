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
    bool checkIntersect(SDL_Rect collider);
    bool checkCollision(SDL_Rect collider);
    void changeDirection(SDL_Rect hitCollider);
    void reset(int screenWidth, int screenHeight, int direction);
    void updatePos(SDL_Rect paddle1, SDL_Rect paddle2, int screenWidth, int screenHeight, float timeStep);
};