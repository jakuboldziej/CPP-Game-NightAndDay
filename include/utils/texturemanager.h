#pragma once

#include "game.h"
#include "utils/texturemanager.h"

class TextureManager
{
public:
  static SDL_Texture *loadTexture(const std::string &texturePath)
  {
    SDL_Surface *tempSurface = IMG_Load(texturePath.c_str());
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
  }

  static void draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip)
  {
    SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &dstRect, 0.0, NULL, flip);
  }
};