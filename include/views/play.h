#pragma once

#include <map>

#include "game.h"
#include "objects/player.h"
#include "ui/button.h"

class Play
{
public:
  Play();
  ~Play();

  void handleEvents(SDL_Event event, GameState &gameState);
  void render(Player *player1, Player *player2);
  void update(Player *player1, Player *player2);

  void initGameEnd(const char *winner);

private:
  bool gameEnded = false;

  std::map<std::string, Button *> buttons;
};