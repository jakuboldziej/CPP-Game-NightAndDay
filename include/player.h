#pragma once

#include "game.h"
#include "gameobject.h"

class Player : public GameObject
{
public:
  Player(const char *textureSheet, int x, int y, int speed = 5);
  ~Player();

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