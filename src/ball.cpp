#include <SDL2/SDL.h>

#include <vector.h>
#include <ball.h>

Ball::Ball(int xPos, int yPos)
{
  mRect.w = 16;
  mRect.h = mRect.w;
  mVelocity = 200;
  mPosition = {(float) xPos, (float) yPos};
  mDirection = {-1.f, 0.f};
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

bool Ball::checkCollision(SDL_Rect collider)
{
  bool colliding = false;
  if(mRect.x>collider.x && mRect.x<collider.x+collider.w)
  {
    if(mRect.y>collider.y && mRect.y<collider.y+collider.h)
    {
      colliding = true;
    }
  }

  return colliding;
}

void Ball::updatePos(SDL_Rect collider1, SDL_Rect collider2, float timeStep)
{
  Vector2 displacement = mDirection*timeStep*mVelocity;
  mPosition += displacement;
  if(checkCollision(collider1))
  {
    mPosition -= displacement;
    mDirection.x*=-1;
  }
  else if(checkCollision(collider2))
  {
    mPosition -= displacement;
    mDirection.x*=-1;
  }
  posToRect();
}