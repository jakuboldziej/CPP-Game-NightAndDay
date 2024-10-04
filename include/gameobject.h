#pragma once

#include <map>
#include <utility>
#include <string>

#include "game.h"
#include "animation.h"

class GameObject
{
public:
  GameObject(const char *textureSheet, int x, int y, bool animated = false, int velocity = 5);

  ~GameObject();

  void render();
  void update();
  void move(int dx, int dy);
  void play(const char *animName);

  void printInfo(const char *name);

  SDL_RendererFlip flip = SDL_FLIP_NONE;

protected:
  int x;
  int y;
  int velocity;
  bool animated = false;
  int frames = 0;
  int frameSpeed = 100;

  SDL_Texture *texture;
  SDL_Rect srcRect, dstRect;

  int animIndex = 0;
  std::map<std::string, Animation> animations;
};