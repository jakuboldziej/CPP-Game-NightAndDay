#include "views/menu.h"

Menu::Menu() {}
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
    if (SDL_PointInRect(&mousePosition, &buttons["Start"]))
    {
      gameState = PLAY;
    }
    else if (SDL_PointInRect(&mousePosition, &buttons["Quit"]))
    {
      isRunning = false;
    }
  }
}

void Menu::render(TTF_Font *font)
{

  int paddingW = 300;
  int paddingH = 50;

  SDL_Point mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  // Menu Title
  SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "MAIN MENU", WHITE);
  SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(Game::renderer, titleSurface);
  SDL_Rect titleRect = {(Game::windowWidth - titleSurface->w - paddingW) / 2, 100, titleSurface->w + paddingW, titleSurface->h + paddingH};
  SDL_RenderCopy(Game::renderer, titleTexture, NULL, &titleRect);

  // Start Option
  SDL_Surface *startSurface = TTF_RenderText_Solid(font, "Start", WHITE);
  SDL_Texture *startTexture = SDL_CreateTextureFromSurface(Game::renderer, startSurface);
  SDL_Rect startRect = {(Game::windowWidth - startSurface->w - paddingW + 200) / 2, 300, startSurface->w + paddingW - 200, startSurface->h + paddingH};
  SDL_RenderCopy(Game::renderer, startTexture, NULL, &startRect);
  buttons.emplace("Start", startRect);

  if (SDL_PointInRect(&mousePosition, &startRect))
  {
    SDL_Surface *startShadowSurface = TTF_RenderText_Solid(font, "Start", GRAY);
    SDL_Texture *startShadowTexture = SDL_CreateTextureFromSurface(Game::renderer, startShadowSurface);
    SDL_Rect startShadowRect = {startRect.x + 2, startRect.y + 2, startRect.w, startRect.h};
    SDL_RenderCopy(Game::renderer, startShadowTexture, NULL, &startShadowRect);

    SDL_FreeSurface(startShadowSurface);
    SDL_DestroyTexture(startShadowTexture);
  }

  // Quit Option
  SDL_Surface *quitSurface = TTF_RenderText_Solid(font, "Quit", WHITE);
  SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(Game::renderer, quitSurface);
  SDL_Rect quitRect = {(Game::windowWidth - quitSurface->w - paddingW + 200) / 2, 500, quitSurface->w + paddingW - 200, quitSurface->h + paddingH};
  SDL_RenderCopy(Game::renderer, quitTexture, NULL, &quitRect);
  buttons.emplace("Quit", quitRect);

  if (SDL_PointInRect(&mousePosition, &quitRect))
  {
    SDL_Surface *quitShadowSurface = TTF_RenderText_Solid(font, "Quit", GRAY);
    SDL_Texture *quitShadowTexture = SDL_CreateTextureFromSurface(Game::renderer, quitShadowSurface);
    SDL_Rect quitShadowRect = {quitRect.x + 2, quitRect.y + 2, quitRect.w, quitRect.h};
    SDL_RenderCopy(Game::renderer, quitShadowTexture, NULL, &quitShadowRect);

    SDL_FreeSurface(quitShadowSurface);
    SDL_DestroyTexture(quitShadowTexture);
  }

  SDL_FreeSurface(titleSurface);
  SDL_FreeSurface(startSurface);
  SDL_FreeSurface(quitSurface);
  SDL_DestroyTexture(titleTexture);
  SDL_DestroyTexture(startTexture);
  SDL_DestroyTexture(quitTexture);

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}