#include <SDL2/SDL.h>
#include <iostream>

#include <vector.h>
#include <ball.h>
#include <gameDataStruct.h>
#include <paddle.h>
#include <timer.h>
#include <window.h>

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

const SDL_Rect& Ball::getCollider() const
{
  return mRect;
}

// Checks if the rects intersects with ball
bool Ball::checkIntersect(SDL_Rect& collider)
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
bool Ball::checkCollision(SDL_Rect& collider)
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

// change direction when based on where it hits a paddle
void Ball::changeDirection(SDL_Rect& hitCollider)
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

void Ball::updatePos(GameData& gameData)
{
  float timeStep = gameData.stepTimer.getTicks()/1000.f;
  Vector2 displacement = mDirection*timeStep*mVelocity;
  mPosition += displacement; // try and move

  SDL_Rect paddle1 = gameData.player1Paddle.getCollider();
  SDL_Rect paddle2 = gameData.player2Paddle.getCollider();
  if(checkCollision(paddle1)) // revert the move if there's any collisions
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
  else if(mRect.y+mRect.h > gameData.window.getHeight() && mDirection.y > 0)
  {
    mPosition -= displacement;
    mDirection.y *= -1;
  }

  if(mRect.x<0)
  {
    reset(gameData.window.getWidth(), gameData.window.getHeight(), 1);
    gameData.player2Score++;
    gameData.player2ScoreText.textureFromText(gameData.window.getRenderer(), std::to_string(gameData.player2Score).c_str(),{0xFF, 0xFF, 0xFF, 0xFF});
  }
  else if(mRect.x+mRect.w>gameData.window.getWidth())
  {
    reset(gameData.window.getWidth(), gameData.window.getHeight(), -1);
    gameData.player1Score++;
    gameData.player1ScoreText.textureFromText(gameData.window.getRenderer(), std::to_string(gameData.player1Score).c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
  }

  posToRect();
}