#include "views/pause.h"
#include "utils/texturemanager.h"
#include "ui/button.h"

Button *pausedBtn;
Button *resumeBtn;
Button *gearBtn;

Pause::Pause()
{
  std::string gearPath = std::string(Game::basePath) + "assets/images/gear.png";

  pausedBtn = new Button("text", 0, 100, "Paused", 6, true);
  resumeBtn = new Button("text", 0, 300, "Resume", 4, true);

  gearBtn = new Button("image", Game::windowWidth - 64, Game::windowHeight - 64, gearPath.c_str(), false);

  buttons.emplace("Resume", resumeBtn);
  buttons.emplace("Gear", gearBtn);
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

    SDL_Rect resumeRect = buttons["Resume"]->getDstRect();
    SDL_Rect gearRect = buttons["Gear"]->getDstRect();

    if (SDL_PointInRect(&mousePosition, &resumeRect))
    {
      gameState = PLAY;
    }
    else if (SDL_PointInRect(&mousePosition, &gearRect))
    {
      gearBtn->click();
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

  // if (SDL_PointInRect(&mousePosition, &resumeRect))
  // {
  //   SDL_Surface *resumeShadowSurface = TTF_RenderText_Solid(font, "Resume", GRAY);
  //   SDL_Texture *resumeShadowTexture = SDL_CreateTextureFromSurface(Game::renderer, resumeShadowSurface);
  //   SDL_Rect shadowRect = {resumeRect.x + 2, resumeRect.y + 2, resumeRect.w, resumeRect.h};
  //   SDL_RenderCopy(Game::renderer, resumeShadowTexture, NULL, &shadowRect);

  //   SDL_FreeSurface(resumeShadowSurface);
  //   SDL_DestroyTexture(resumeShadowTexture);
  // }

  for (const auto &buttonPair : buttons)
  {
    buttonPair.second->render();
  }

  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}