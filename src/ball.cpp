#include <SDL2/SDL.h>

#include <vector.h>
#include <ball.h>

Ball::Ball(int xPos, int yPos)
{
  mRect.w = 16;
  mRect.h = mRect.w;
  mVelocity = 400;
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

// Checks if the rects intersects with ball
bool Ball::checkIntersect(SDL_Rect collider)
{
  bool intersect = false;
  if(mRect.x>collider.x && mRect.x<collider.x+collider.w)
  {
    intersect = true;
  }
  else if(mRect.x+mRect.w>collider.x && mRect.x+mRect.w<collider.x+collider.w)
  {
    intersect = true;
  }
  
  if(mRect.y>collider.y && mRect.y<collider.y+collider.h){}
  else if(mRect.y+mRect.h>collider.y && mRect.y+mRect.h<collider.y+collider.h){}
  else
  {
    intersect = false;
  }

  return intersect;
}

// Checks for collision on direction of travel
bool Ball::checkCollision(SDL_Rect collider)
{
  bool colliding = false;

  if(mDirection.x<0) // check only colliders on the left
  {
    if(collider.x<mRect.x) // therefore collider is to left
    {
      colliding = checkIntersect(collider);
    }
  }
  else if(mDirection.x>0) // check only colliders on the right
  {
    if(collider.x>mRect.x) // therefore collider is to right
    {
      colliding = checkIntersect(collider);
    }
  }
  return colliding;
}

// change direction when hitting a paddle
void Ball::changeDirection(SDL_Rect hitCollider)
{
  float tempName = mPosition.y;
  tempName -= hitCollider.y;
  tempName*=(2.f/hitCollider.h);
  tempName-=1;
  mDirection.y = tempName;

  mDirection.x *= -1;
}

void Ball::reset(int screenWidth, int screenHeight, int direction)
{
  mPosition = {(float) screenWidth/2, (float) screenHeight/2};
  mDirection = {(float) direction, 0};
}

void Ball::updatePos(SDL_Rect paddle1, SDL_Rect paddle2, int screenWidth, int screenHeight,float timeStep)
{
  Vector2 displacement = mDirection*timeStep*mVelocity;
  mPosition += displacement;
  if(checkCollision(paddle1))
  {
    mPosition -= displacement;
    changeDirection(paddle1);
  }
  else if(checkCollision(paddle2))
  {
    mPosition -= displacement;
    changeDirection(paddle2);
  }

  if(mRect.y<0 && mDirection.y<0)
  {
    mPosition -= displacement;
    mDirection.y *= -1;
  }
  else if(mRect.y+mRect.h>screenHeight && mDirection.y>0)
  {
    mPosition -= displacement;
    mDirection.y *= -1;
  }

  if(mRect.x<0)
  {
    reset(screenWidth, screenHeight, 1);
  }
  else if(mRect.x+mRect.w>screenWidth)
  {
    reset(screenWidth, screenHeight, -1);
  }

  posToRect();
}