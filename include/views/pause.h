#pragma once

#include "game.h"
#include <map>

#include "ui/button.h"

class Pause
{
public:
  Pause();
  ~Pause();

  void handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState);
  void render(TTF_Font *font);

private:
  SDL_Texture *gearTexture;
  std::map<std::string, Button *> buttons;
};