#pragma once
class Window;
class Paddle;
class Ball;
class Timer;

struct GameData
{
	Window& window;
	Paddle& player1Paddle;
	Paddle& player2Paddle;
	Ball& ball;
	Timer& stepTimer;
	const int paddleVelocity;
  int player1Score;
  int player2Score;
};