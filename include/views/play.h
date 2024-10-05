#pragma once

#include <map>

#include "game.h"
#include "objects/player.h"

class Play
{
public:
  Play();
  ~Play();

  void handleEvents(SDL_Event event, GameState &gameState);
  void render(Player *player);
  void update(Player *player);

private:
  std::map<std::string, SDL_Rect> buttons;
};