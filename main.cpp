#include <stdlib.h>
#include <crtdbg.h>

#include "game.h"

Game *game;

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  const int FPS = 165;
  const int frameDelay = 1000 / FPS;

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

  _CrtDumpMemoryLeaks();

  return 0;
}