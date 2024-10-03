#include "gameobject.h"
#include "texturemanager.h"

int windowWidth, windowHeight;

GameObject::GameObject(const char *textureSheet, int x, int y, int speed)
{
  try
  {
    texture = TextureManager::LoadTexture(textureSheet);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  if (texture == nullptr)
  {
    std::cerr << "Failed to load texture: " << textureSheet << std::endl;
    return;
  }

  this->x = x;
  this->y = y;
  this->speed = speed;

  SDL_GetRendererOutputSize(Game::renderer, &windowWidth, &windowHeight);
}

GameObject::~GameObject() {}

void GameObject::render()
{
  SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

void GameObject::update()
{
  srcRect.w = 128;
  srcRect.h = 128;
  srcRect.x = 0;
  srcRect.y = 0;

  dstRect.w = srcRect.w;
  dstRect.h = srcRect.h;
  dstRect.x = x;
  dstRect.y = y;
}

void GameObject::move(int dx, int dy)
{
  if (x + dx * speed < 0 || x + dx * speed + dstRect.w > windowWidth)
    dx = 0;

  if (y + dy * speed < 0 || y + dy * speed + dstRect.h > windowHeight)
    dy = 0;

  x += dx * speed;
  y += dy * speed;
}

void GameObject::printInfo(const char *name)
{
  std::cout << name << ": x: " << x << " y: " << y << std::endl;
  // std::cout << "srcRect: " << srcRect.x << " " << srcRect.y << " " << srcRect.w << " " << srcRect.h << std::endl;
}