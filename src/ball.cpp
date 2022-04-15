#include <SDL2/SDL.h>

#include <vector.h>
#include <ball.h>

Ball::Ball(int velocity, int xPos, int yPos)
{
  mRect.w = 16;
  mRect.h = mRect.w;
  mVelocity = velocity;
  mPosition = {(float) xPos, (float) yPos};
  mDirection = {1.f, 0.f};
  posToRect();
}

void Ball::posToRect()
{
  mRect.x = (int) (mPosition.x - mRect.w/2);
  mRect.y = (int) (mPosition.y - mRect.h/2);
}

SDL_Rect Ball::getCollider()
{
  return mRect;
}

void Ball::updatePos(SDL_Rect collider1, SDL_Rect collider2, float timeStep)
{
  mPosition + timeStep*mVelocity;
}