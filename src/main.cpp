#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include <window.h>
#include <paddle.h>
#include <timer.h>
#include <gameDataStruct.h>
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

	if(TTF_Init() == -1)
	{
		printf("Failed to initialise SDL_ttf. SDL_ttf Error: %s\n", TTF_GetError());
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

void handleEvents(SDL_Event& e, bool& exit, KeyData& keyData)
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
	
	int playerDirection = 0;
	if(keyData.wKeyDown)
	{
		playerDirection = -1; // Negative because y=0 is at top of screen
	}
	else if(keyData.sKeyDown)
	{
		playerDirection = 1;
	}
	gameData.player1Paddle.updateYPos(playerDirection*distance, gameData.window.getHeight());

	int opponentDirection = 0;
	if(keyData.upKeyDown)
	{
		opponentDirection = -1; // Negative because y=0 is at top of screen
	}
	else if(keyData.downKeyDown)
	{
		opponentDirection = 1;
	}
	gameData.player2Paddle.updateYPos(opponentDirection*distance, gameData.window.getHeight());

	gameData.ball.updatePos(gameData);

	gameData.stepTimer.Start();
}

void gameLoop(Window& window)
{
	bool exit = false;
	SDL_Event e;
	Paddle player1Paddle(20, (SCREEN_HEIGHT-50)/2);                  // 50 is the paddle's height
	Paddle player2Paddle(SCREEN_WIDTH - 30, (SCREEN_HEIGHT-50)/2); // 30 as we want 20 padding and paddle is 10 wide
	Ball ball(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	Timer stepTimer;
	Text player1ScoreText;
	Text player2ScoreText;
	int paddleVelocity{400};
	int player1Score = 0;
	int player2Score = 0;

	GameData gameData{window, player1Paddle, player2Paddle, ball, stepTimer, player1ScoreText, player2ScoreText, paddleVelocity, player1Score, player2Score};
	KeyData keyData;

	player1ScoreText.openFont("Assets/OpenSans-Regular.ttf", 40);
	player2ScoreText.openFont("Assets/OpenSans-Regular.ttf", 40);
	player1ScoreText.textureFromText(window.getRenderer(),"0",{0xFF, 0xFF, 0xFF, 0xFF});
	player2ScoreText.textureFromText(window.getRenderer(),"0",{0xFF, 0xFF, 0xFF, 0xFF});
	while(!exit)
	{
		handleEvents(e, exit, keyData);
		handleMovement(gameData, keyData);

		window.clearRender();
		window.renderPaddle(player1Paddle);
		window.renderPaddle(player2Paddle);
		window.renderText(player1ScoreText, (SCREEN_WIDTH/4)-(player1ScoreText.getWidth()/2), 20);
		window.renderText(player2ScoreText, (3*SCREEN_WIDTH/4)-(player2ScoreText.getWidth()/2), 20);
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

	TTF_Quit();
	SDL_Quit();
	return 0;
}