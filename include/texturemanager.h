#pragma once

#include "game.h"

class TextureManager
{
public:
  static SDL_Texture *loadTexture(const std::string &texturePath);
  static void draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip);
};