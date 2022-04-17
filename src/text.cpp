#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include <text.h>

Text::Text()
{
  mFont = NULL;
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Text::~Text()
{
  if(mFont != NULL)
  {
    TTF_CloseFont(mFont);
    mFont = NULL;
  }
  free();
}

void Text::free()
{
  if(mTexture != NULL)
  {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void Text::openFont(const char* path, int fontSize)
{
  if(mFont != NULL)
  {
    TTF_CloseFont(mFont); // if exists close old font first
  }

  mFont = TTF_OpenFont(path, fontSize);
  if(mFont == NULL)
  {
    printf("Failed to load font: %s, SDL_ttf Error: %s\n", path, TTF_GetError());
  }
}

void Text::textureFromText(SDL_Renderer* renderer, const char* text, SDL_Color textColor)
{
  if(mFont == NULL){return;}

  SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text, textColor);
  if(textSurface == NULL)
  {
    printf("Unable to render text surface. SDL_ttf Error: %s\nText: %s\n", TTF_GetError(), text);
    return;
  }

  mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if(mTexture == NULL)
  {
    printf("Unable to create texture from rendered text. SDL Error: %s\nText: %s\n", SDL_GetError(), text);
    return;
  }

  mWidth = textSurface->w;
  mHeight = textSurface->h;
  SDL_FreeSurface(textSurface);
}

int Text::getHeight() const
{
  return mHeight;
}

int Text::getWidth() const
{
  return mWidth;
}

SDL_Texture* Text::getTexture() const
{
  return mTexture;
}