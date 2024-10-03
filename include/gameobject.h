#pragma once

#include <utility>

#include "game.h"

class GameObject
{
public:
  GameObject(const char *textureSheet, int x, int y, int speed = 5);
  ~GameObject();

  void render();
  void update();
  void move(int dx, int dy);

  void printInfo(const char *name);

private:
  int x;
  int y;
  int speed;

  SDL_Texture *texture;
  SDL_Rect srcRect, dstRect;
};