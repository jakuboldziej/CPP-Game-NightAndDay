#include <stdlib.h>

#include "game.h"

Game *game;

int main()
{
  Uint32 frameStart;
  int frameTime;

  game = new Game();
  game->init("Night And Day", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

  while (game->running())
  {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime)
    {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game->clean();

  delete game;

  return 0;
}