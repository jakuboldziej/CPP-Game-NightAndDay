#pragma once

#include "game.h"
#include <map>

class Pause
{
public:
  Pause();
  ~Pause();

  void handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState);
  void render(TTF_Font *font);

private:
  std::map<std::string, SDL_Rect> buttons;
};