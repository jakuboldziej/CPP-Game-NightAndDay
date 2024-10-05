#include "views/pause.h"
#include "utils/texturemanager.h"
#include "ui/button.h"

Button *pausedBtn;

Pause::Pause()
{
  pausedBtn = new Button("text", 0, Game::fullscreen ? 162 * 1.5 : 162, "Paused", 6, true);
  buttons["Resume"] = new Button("text", 0, Game::fullscreen ? 341 * 1.5 : 341, "Resume", 4, true);
  buttons["Main menu"] = new Button("text", 0, Game::fullscreen ? 493 * 1.5 : 493, "Main menu", 4, true);

  std::string gearPath = std::string(Game::basePath) + "assets/images/gear.png";
  buttons["Gear"] = new Button("image", Game::windowWidth - 64, Game::windowHeight - 64, gearPath.c_str(), false);
}

Pause::~Pause() {}

void Pause::handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState)
{
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
  {
    gameState = PLAY;
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect resumeBtnRect = buttons["Resume"]->getDstRect();
    SDL_Rect mainMenuBtnRect = buttons["Main menu"]->getDstRect();
    SDL_Rect gearBtnRect = buttons["Gear"]->getDstRect();

    if (SDL_PointInRect(&mousePosition, &resumeBtnRect))
    {
      gameState = PLAY;
    }
    else if (SDL_PointInRect(&mousePosition, &mainMenuBtnRect))
    {
      gameState = MENU;
    }
    else if (SDL_PointInRect(&mousePosition, &gearBtnRect))
    {
      std::cout << "Settings" << std::endl;
    }
  }
}

void Pause::render(TTF_Font *font)
{
  int paddingW = 300;
  int paddingH = 50;

  SDL_Point mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  pausedBtn->render();

  buttons["Resume"]->render(true);

  buttons["Main menu"]->render(true);

  buttons["Gear"]->render();

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}