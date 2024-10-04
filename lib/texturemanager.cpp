#include "texturemanager.h"

SDL_Texture *TextureManager::loadTexture(const std::string &texturePath)
{
  SDL_Surface *tempSurface = IMG_Load(texturePath.c_str());
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}

void TextureManager::draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
  SDL_RenderCopyEx(Game::renderer, texture, &src, &dst, 0.0, NULL, flip);
}