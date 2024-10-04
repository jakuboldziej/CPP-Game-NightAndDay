#include "views/pause.h"

Pause::Pause() {}
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
    if (SDL_PointInRect(&mousePosition, &buttons["Resume"]))
    {
      gameState = PLAY;
    }
  }
}

void Pause::render(TTF_Font *font)
{
  SDL_Color white = {255, 255, 255};

  int paddingW = 300;
  int paddingH = 50;

  SDL_Surface *pauseSurface = TTF_RenderText_Solid(font, "PAUSED", white);
  SDL_Texture *pauseTexture = SDL_CreateTextureFromSurface(Game::renderer, pauseSurface);
  SDL_Rect pauseRect = {(Game::windowWidth - pauseSurface->w - paddingW) / 2, 100, pauseSurface->w + paddingW, pauseSurface->h + paddingH};
  SDL_RenderCopy(Game::renderer, pauseTexture, NULL, &pauseRect);

  SDL_Surface *resumeSurface = TTF_RenderText_Solid(font, "RESUME", white);
  SDL_Texture *resumeTexture = SDL_CreateTextureFromSurface(Game::renderer, resumeSurface);
  SDL_Rect resumeRect = {(Game::windowWidth - resumeSurface->w - paddingW + 120) / 2, 300, resumeSurface->w + paddingW - 120, resumeSurface->h + paddingH - 20};
  SDL_RenderCopy(Game::renderer, resumeTexture, NULL, &resumeRect);
  buttons.emplace("Resume", resumeRect);

  SDL_FreeSurface(pauseSurface);
  SDL_FreeSurface(resumeSurface);
  SDL_DestroyTexture(pauseTexture);
  SDL_DestroyTexture(resumeTexture);
  TTF_CloseFont(font);

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}