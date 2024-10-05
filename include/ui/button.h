#pragma once

#include <map>

#include "game.h"
#include "utils/texturemanager.h"
#include <utility>

class Button
{
public:
  Button(const char *typeStr, int x, int y, const char *btnText, int scale = 1, bool center = false)
      : typeStr(typeStr), x(x), y(y), scale(scale), center(center)
  {
    if (strcmp(typeStr, "image") == 0)
    {
      initImage(btnText);
    }
    else if (strcmp(typeStr, "text") == 0)
    {
      initText(btnText);
    }

    srcRect.x = srcRect.y = 0;
  }

  ~Button() {}

  void render(bool shadow = false)
  {
    if (strcmp(typeStr, "image") == 0)
    {
      TextureManager::draw(texture, srcRect, dstRect, flip);
    }
    else if (strcmp(typeStr, "text") == 0)
    {
      SDL_RenderCopy(Game::renderer, texture, NULL, &dstRect);

      if (shadow == true)
      {
        SDL_Point mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (SDL_PointInRect(&mousePosition, &dstRect))
        {
          SDL_RenderCopy(Game::renderer, shadowTexture, NULL, &shadowRect);
        }
      }
    }

    // Hitbox
    // SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect(Game::renderer, &dstRect);
  }

  SDL_Rect getDstRect() { return dstRect; }

  void printInfo()
  {
    // std::cout << "|" << typeStr << "| " << std::endl;
    std::cout << "|" << typeStr << "| " << "dstRect - x: " << dstRect.x << " y: " << dstRect.y << " w: " << dstRect.w << " h: " << dstRect.h << std::endl;
  }

  SDL_RendererFlip flip = SDL_FLIP_NONE;

protected:
  int x;
  int y;
  int scale;
  bool center;
  const char *typeStr;

  SDL_Texture *texture;
  SDL_Texture *shadowTexture;
  SDL_Rect srcRect, dstRect, shadowRect;

  void initImage(const char *btnText)
  {
    int buttonWidth, buttonHeight;

    try
    {
      texture = TextureManager::loadTexture(btnText);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
    if (texture == nullptr)
    {
      std::cerr << "Failed to load texture: " << btnText << std::endl;
      return;
    }

    SDL_QueryTexture(texture, NULL, NULL, &buttonWidth, &buttonHeight);

    srcRect.x = srcRect.y = 0;
    srcRect.w = buttonWidth;
    srcRect.h = buttonHeight;

    if (center)
      dstRect.x = (Game::windowWidth - buttonWidth) / 2;
    else
      dstRect.x = x;

    dstRect.y = y;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
  }

  void initText(const char *name)
  {
    SDL_Surface *buttonSurface = TTF_RenderText_Solid(Game::font, name, WHITE);
    texture = SDL_CreateTextureFromSurface(Game::renderer, buttonSurface);

    int scaledWidth = buttonSurface->w * scale;
    int scaledHeight = buttonSurface->h * scale;

    if (center)
      dstRect.x = (Game::windowWidth - scaledWidth) / 2;
    else
      dstRect.x = x;
    dstRect.y = y;
    dstRect.w = scaledWidth;
    dstRect.h = scaledHeight;

    SDL_Surface *shadowSurface = TTF_RenderText_Solid(Game::font, name, GRAY);
    shadowTexture = SDL_CreateTextureFromSurface(Game::renderer, shadowSurface);

    shadowRect.x = dstRect.x + 2;
    shadowRect.y = dstRect.y + 2;
    shadowRect.w = dstRect.w;
    shadowRect.h = dstRect.h;

    // SDL_FreeSurface(buttonSurface);
    // SDL_DestroyTexture(texture);
  }
};