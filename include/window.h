#pragma once
#include <SDL2/SDL.h>

#include <paddle.h>
#include <ball.h>

class Window
{
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        int mWidth;
        int mHeight;
        SDL_Color mBackgroundColor;
    public:
        Window();
        Window(SDL_Color backgroundColor);
        ~Window();
        bool create(const char* title, int width, int height);
        void renderRect(const SDL_Rect& rect, SDL_Color& color, bool filled);
        void renderPaddle(const Paddle& paddle);
        void renderBall(const Ball& ball);
        void clearRender();
        void updateRender();
        int getHeight() const;
        int getWidth() const;
};