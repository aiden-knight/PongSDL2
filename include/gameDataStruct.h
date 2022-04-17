#pragma once
class Window;
class Paddle;
class Ball;
class Timer;
class Text;

struct GameData
{
	Window& window;
	Paddle& player1Paddle;
	Paddle& player2Paddle;
	Ball& ball;
	Timer& stepTimer;
	Text& player1ScoreText;
	Text& player2ScoreText;
	const int paddleVelocity;
  int player1Score;
  int player2Score;
};