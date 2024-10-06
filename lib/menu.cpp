#include "views/menu.h"
#include "ui/button.h"

Button *mainMenu;

Menu::Menu()
{
  mainMenu = new Button("text", 0, Game::fullscreen ? 162 * 1.5 : 162, "MAIN MENU", 6, true);
  buttons["Start"] = new Button("text", 0, Game::fullscreen ? 341 * 1.5 : 341, "Start", 4, true);
  buttons["Quit"] = new Button("text", 0, Game::fullscreen ? 493 * 1.5 : 493, "Quit", 4, true);

  std::string gearPath = std::string(Game::basePath) + "assets/images/gear.png";
  buttons["Gear"] = new Button("image", Game::windowWidth - 64, Game::windowHeight - 64, gearPath.c_str(), false);
}

Menu::~Menu() {}

void Menu::handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState, bool &isRunning)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_RETURN)
    {
      Game::clearGameEntites();
      Game::initGameEntites();
      gameState = PLAY;
    }
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect startRect = buttons["Start"]->getDstRect();
    SDL_Rect quitRect = buttons["Quit"]->getDstRect();
    SDL_Rect gearBtnRect = buttons["Gear"]->getDstRect();

    if (SDL_PointInRect(&mousePosition, &startRect))
    {
      Game::clearGameEntites();
      Game::initGameEntites();
      gameState = PLAY;
    }
    else if (SDL_PointInRect(&mousePosition, &quitRect))
    {
      isRunning = false;
    }
    else if (SDL_PointInRect(&mousePosition, &gearBtnRect))
    {
      std::cout << "Settings" << std::endl;
    }
  }
}

void Menu::render()
{
  int paddingW = 300;
  int paddingH = 50;

  SDL_Point mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  mainMenu->render();

  buttons["Start"]->render(true);

  buttons["Quit"]->render(true);

  buttons["Gear"]->render();

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}