#pragma once

#include <map>

#include "game.h"
#include "ui/button.h"

class Menu
{
public:
  Menu();
  ~Menu();

  void handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState, bool &isRunning);
  void render();

private:
  std::map<std::string, Button *> buttons;
};