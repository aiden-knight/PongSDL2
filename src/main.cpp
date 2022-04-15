#include <SDL2/SDL.h>
#include <stdio.h>

#include <window.h>
#include <paddle.h>
#include <timer.h>
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct KeyData
{
	bool upKeyDown = false,
		 wKeyDown  = false,
		 downKeyDown = false,
		 sKeyDown = false;
};

struct GameData
{
	Window& window;
	Paddle& playerPaddle;
	Paddle& opponentPaddle;
	Ball& ball;
	Timer& stepTimer;
	int opponentDirection;
	const int paddleVelocity;
};

// Returns false on error
bool init(Window& window)
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{ 
		printf("Failed to initialise SDL2. SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if(!window.create("Pong", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Window creation failed.\n");
		return false;
	}
	return true;
}

void keyEvents(SDL_Keycode keyCode, KeyData& keyData, bool keyDown)
{
	switch(keyCode)
	{
		case SDLK_UP:
			keyData.upKeyDown = keyDown;
			break;
		case SDLK_w:
			keyData.wKeyDown = keyDown;
			break;
		case SDLK_DOWN:
			keyData.downKeyDown = keyDown;
			break;
		case SDLK_s:
			keyData.sKeyDown = keyDown;
			break;
	}
}

void handleEvents(SDL_Event e, bool& exit, KeyData& keyData)
{
	while(SDL_PollEvent(&e)!=0)
	{
		switch(e.type)
		{
			case SDL_QUIT:
				exit = true;
				break;
			case SDL_KEYDOWN:
				keyEvents(e.key.keysym.sym, keyData, true);
				break;
			case SDL_KEYUP:
				keyEvents(e.key.keysym.sym, keyData, false);
				break;
		}
	}
}

void handleMovement(GameData& gameData, KeyData& keyData)
{
	float distance = gameData.paddleVelocity*gameData.stepTimer.getTicks()/1000.f;
	int direction = 0;
	if(keyData.upKeyDown||keyData.wKeyDown)
	{
		direction = -1; // Negative because y=0 is at top of screen
	}
	else if(keyData.downKeyDown||keyData.sKeyDown)
	{
		direction = 1;
	}
	gameData.playerPaddle.updateYPos(direction*distance, gameData.window.getHeight());

	// if(gameData.opponentPaddle.updateYPos(gameData.opponentDirection*distance, gameData.window.getHeight()))
	// {
	// 	gameData.opponentDirection*=-1;
	// }

	gameData.ball.updatePos(gameData.playerPaddle.getCollider(), gameData.opponentPaddle.getCollider(), gameData.stepTimer.getTicks()/1000.f);

	gameData.stepTimer.Start();
}

void gameLoop(Window& window)
{
	bool exit = false;
	SDL_Event e;
	Paddle playerPaddle(20, (SCREEN_HEIGHT-50)/2);                  // 50 is the paddle's height
	Paddle opponentPaddle(SCREEN_WIDTH - 30, (SCREEN_HEIGHT-50)/2); // 30 as we want 20 padding and paddle is 10 wide
	Ball ball(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	int opponentDirection{1};                                       // 1 or -1 for up or down
	Timer stepTimer;
	int paddleVelocity{300};

	GameData gameData{window, playerPaddle,opponentPaddle, ball, stepTimer, opponentDirection, paddleVelocity};
	KeyData keyData;
	while(!exit)
	{
		handleEvents(e, exit, keyData);
		handleMovement(gameData, keyData);

		window.clearRender();
		window.renderPaddle(playerPaddle);
		window.renderPaddle(opponentPaddle);
		window.renderBall(ball);
		window.updateRender();
	}
}

int main(int argc, char* args[])
{
	Window window({0x00, 0x00, 0x00, 0xFF}); // Constructs a window with black bg color
	if(!init(window))
	{
		printf("Failed to initialise.\n");
		return 0;
	}
	gameLoop(window);

	SDL_Quit();
	return 0;
}