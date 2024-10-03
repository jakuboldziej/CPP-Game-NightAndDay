#pragma once

#include "game.h"

class TextureManager
{
public:
  static SDL_Texture *LoadTexture(const std::string &texturePath);
  static void Draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect);
};