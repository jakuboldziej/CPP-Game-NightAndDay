#include "views/pause.h"
#include "utils/texturemanager.h"

Pause::Pause()
{
  std::string gearPath = std::string(Game::basePath) + "assets/images/gear.png";
  gearTexture = TextureManager::loadTexture(gearPath);
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
    if (SDL_PointInRect(&mousePosition, &buttons["Resume"]))
    {
      gameState = PLAY;
    }
  }
}

void Pause::render(TTF_Font *font)
{
  int paddingW = 300;
  int paddingH = 50;

  SDL_Point mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  SDL_Surface *pauseSurface = TTF_RenderText_Solid(font, "PAUSED", WHITE);
  SDL_Texture *pauseTexture = SDL_CreateTextureFromSurface(Game::renderer, pauseSurface);
  SDL_Rect pauseRect = {(Game::windowWidth - pauseSurface->w - paddingW) / 2, 100, pauseSurface->w + paddingW, pauseSurface->h + paddingH};
  SDL_RenderCopy(Game::renderer, pauseTexture, NULL, &pauseRect);

  SDL_Surface *resumeSurface = TTF_RenderText_Solid(font, "Resume", WHITE);
  SDL_Texture *resumeTexture = SDL_CreateTextureFromSurface(Game::renderer, resumeSurface);
  SDL_Rect resumeRect = {(Game::windowWidth - resumeSurface->w - paddingW + 120) / 2, 300, resumeSurface->w + paddingW - 120, resumeSurface->h + paddingH - 20};
  SDL_RenderCopy(Game::renderer, resumeTexture, NULL, &resumeRect);
  buttons.emplace("Resume", resumeRect);

  if (SDL_PointInRect(&mousePosition, &resumeRect))
  {
    SDL_Surface *resumeShadowSurface = TTF_RenderText_Solid(font, "Resume", GRAY);
    SDL_Texture *resumeShadowTexture = SDL_CreateTextureFromSurface(Game::renderer, resumeShadowSurface);
    SDL_Rect shadowRect = {resumeRect.x + 2, resumeRect.y + 2, resumeRect.w, resumeRect.h};
    SDL_RenderCopy(Game::renderer, resumeShadowTexture, NULL, &shadowRect);

    SDL_FreeSurface(resumeShadowSurface);
    SDL_DestroyTexture(resumeShadowTexture);
  }

  TextureManager::draw(gearTexture, {0, 0, 64, 64}, {0, 0, 64, 64});

  SDL_FreeSurface(pauseSurface);
  SDL_FreeSurface(resumeSurface);
  SDL_DestroyTexture(pauseTexture);
  SDL_DestroyTexture(resumeTexture);

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}