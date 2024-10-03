#include "texturemanager.h"

SDL_Texture *TextureManager::LoadTexture(const std::string &texturePath)
{
  SDL_Surface *tempSurface = IMG_Load(texturePath.c_str());
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst)
{
  SDL_RenderCopy(Game::renderer, texture, &src, &dst);
}