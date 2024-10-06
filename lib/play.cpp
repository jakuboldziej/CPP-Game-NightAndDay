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

void Play::render(Player *player1, Player *player2)
{
  player1->render();
  // player2->render();

  SDL_SetRenderDrawColor(Game::renderer, 60, 60, 60, 255);
}

void Play::update(Player *player1, Player *player2)
{
  const Uint8 *state = SDL_GetKeyboardState(nullptr);

  // Movement
  if (state[SDL_SCANCODE_W])
  {
    if (player1->isOnGround())
      player1->jump();
  }
  if (state[SDL_SCANCODE_A])
  {
    player1->move(-1, 0);
    player1->play("Run");
    player1->flip = SDL_FLIP_HORIZONTAL;
  }
  else if (state[SDL_SCANCODE_D])
  {
    player1->move(1, 0);
    player1->play("Run");
    player1->flip = SDL_FLIP_NONE;
  }
  else if (player1->isOnGround())
    player1->play("Idle");

  player1->update();

  // player2->play("Idle");
  // player2->update();

  player1->printInfo("Player1");
  // player2->printInfo("Player2");
}