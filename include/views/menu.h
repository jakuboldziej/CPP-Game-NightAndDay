#pragma once

#include "game.h"
#include <map>

class Menu
{
public:
  Menu();
  ~Menu();

  void handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState, bool &isRunning);
  void render(TTF_Font *font);

private:
  std::map<std::string, SDL_Rect> buttons;
};