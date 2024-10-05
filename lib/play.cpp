#include "views/play.h"

Play::Play() {}
Play::~Play() {}

void Play::handleEvents(SDL_Event event, GameState &gameState)
{
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
  {
    gameState = PAUSE;
  }
}

void Play::render(Player *player)
{
  player->render();

  SDL_SetRenderDrawColor(Game::renderer, 60, 60, 60, 255);
}

void Play::update(Player *player)
{
  const Uint8 *state = SDL_GetKeyboardState(nullptr);

  // Movement
  if (state[SDL_SCANCODE_SPACE])
  {
    if (player->isOnGround())
      player->jump();
  }
  if (state[SDL_SCANCODE_A])
  {
    player->move(-1, 0);
    player->play("Run");
    player->flip = SDL_FLIP_HORIZONTAL;
  }
  else if (state[SDL_SCANCODE_D])
  {
    player->move(1, 0);
    player->play("Run");
    player->flip = SDL_FLIP_NONE;
  }
  else
    player->play("Idle");

  player->update();
  player->printInfo("Player");
}