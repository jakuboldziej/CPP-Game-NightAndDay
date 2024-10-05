#include "views/menu.h"
#include "ui/button.h"

Button *startBtn;
Button *quitBtn;
Button *mainMenuBtn;

Menu::Menu()
{
  mainMenuBtn = new Button("text", 0, 100, "MAIN MENU", 6, true);
  startBtn = new Button("text", 0, 300, "Start", 4, true);
  quitBtn = new Button("text", 0, 500, "Quit", 4, true);

  buttons.emplace("Start", startBtn);
  buttons.emplace("Quit", quitBtn);
}
Menu::~Menu() {}

void Menu::handleEvents(SDL_Point &mousePosition, SDL_Event event, GameState &gameState, bool &isRunning)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_RETURN:
      gameState = PLAY;
      break;
    case SDLK_ESCAPE:
      isRunning = false;
      break;
    default:
      break;
    }
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect startRect = buttons["Start"]->getDstRect();
    SDL_Rect quitRect = buttons["Quit"]->getDstRect();

    if (SDL_PointInRect(&mousePosition, &startRect))
    {
      gameState = PLAY;
    }
    else if (SDL_PointInRect(&mousePosition, &quitRect))
    {
      isRunning = false;
    }
  }
}

void Menu::render()
{
  int paddingW = 300;
  int paddingH = 50;

  SDL_Point mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  // Menu Title
  mainMenuBtn->render();

  // Start Option
  startBtn->render();

  // if (SDL_PointInRect(&mousePosition, &startBtn->getDstRect()))
  // {
  //   SDL_Surface *startShadowSurface = TTF_RenderText_Solid(Game::font, "Start", GRAY);
  //   SDL_Texture *startShadowTexture = SDL_CreateTextureFromSurface(Game::renderer, startShadowSurface);
  //   SDL_Rect startShadowRect = {startBtn->getDstRect().x + 2, startBtn->getDstRect().y + 2, startBtn->getDstRect().w, startBtn->getDstRect().h};
  //   SDL_RenderCopy(Game::renderer, startShadowTexture, NULL, &startShadowRect);

  //   SDL_FreeSurface(startShadowSurface);
  //   SDL_DestroyTexture(startShadowTexture);
  // }

  // Quit Option
  quitBtn->render();

  // if (SDL_PointInRect(&mousePosition, &quitRect))
  // {
  //   SDL_Surface *quitShadowSurface = TTF_RenderText_Solid(Game::font, "Quit", GRAY);
  //   SDL_Texture *quitShadowTexture = SDL_CreateTextureFromSurface(Game::renderer, quitShadowSurface);
  //   SDL_Rect quitShadowRect = {quitRect.x + 2, quitRect.y + 2, quitRect.w, quitRect.h};
  //   SDL_RenderCopy(Game::renderer, quitShadowTexture, NULL, &quitShadowRect);

  //   SDL_FreeSurface(quitShadowSurface);
  //   SDL_DestroyTexture(quitShadowTexture);
  // }

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}