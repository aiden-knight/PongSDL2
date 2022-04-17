#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text
{
  private:
    TTF_Font* mFont;
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
  public:
    Text();
    ~Text();
    void free();
    void openFont(const char* path, int fontSize);
    void textureFromText(SDL_Renderer* renderer, const char* text, SDL_Color textColor);
    int getHeight() const;
    int getWidth() const;
    SDL_Texture* getTexture() const;
};