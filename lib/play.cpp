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
  player2->render();

  // Healthbars

  SDL_Rect player1Healthbar = {10, 10, 400, 40};
  SDL_Rect player2Healthbar = {Game::windowWidth - 410, 10, 400, 40};

  SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(Game::renderer, &player1Healthbar);
  SDL_RenderFillRect(Game::renderer, &player2Healthbar);

  float player1HealthPercentage = static_cast<float>(player1->getCurrentHealth()) / player1->getMaxHealth();
  float player2HealthPercentage = static_cast<float>(player2->getCurrentHealth()) / player2->getMaxHealth();

  SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
  SDL_Rect player1HealthFill = {
      player1Healthbar.x,
      player1Healthbar.y,
      static_cast<int>(player1Healthbar.w * player1HealthPercentage),
      player1Healthbar.h};

  SDL_RenderFillRect(Game::renderer, &player1HealthFill);

  SDL_Rect player2HealthFill = {
      player2Healthbar.x,
      player2Healthbar.y,
      static_cast<int>(player2Healthbar.w * player2HealthPercentage),
      player2Healthbar.h};

  SDL_RenderFillRect(Game::renderer, &player2HealthFill);

  SDL_SetRenderDrawColor(Game::renderer, 60, 60, 60, 255);
}

void Play::update(Player *player1, Player *player2)
{
  const Uint8 *state = SDL_GetKeyboardState(nullptr);

  // Player 1

  // Movement
  if (player1->canMove())
  {
    if (state[SDL_SCANCODE_W])
    {
      if (player1->isOnGround())
      {
        player1->takeDamage(20);

        player1->jump();
      }
    }
    if (state[SDL_SCANCODE_A])
    {
      player1->move(-1, 0);
      if (player1->isOnGround())
        player1->play("Run");
      player1->flip = SDL_FLIP_HORIZONTAL;
    }
    else if (state[SDL_SCANCODE_D])
    {
      player1->move(1, 0);
      if (player1->isOnGround())
        player1->play("Run");
      player1->flip = SDL_FLIP_NONE;
    }
    else if (player1->isOnGround())
      player1->play("Idle");
  }

  // attacking
  if (state[SDL_SCANCODE_X])
  {
    if (!player1->isAttacking())
      player1->attack("SwingBackhand");
  }
  else if (state[SDL_SCANCODE_C])
  {
    if (!player1->isAttacking())
      player1->attack("SwingForehand");
  }
  else if (state[SDL_SCANCODE_V])
  {
    if (!player1->isAttacking())
      player1->attack("SwingDiagonal");
  }
  else if (state[SDL_SCANCODE_B])
  {
    if (!player1->isBlocking())
      player1->block();
  }

  // Blocking
  if (state[SDL_SCANCODE_B])
  {
    if (!player1->isBlocking())
      player1->block();
  }
  else
  {
    if (player1->isBlocking())
    {
      std::cout << "Stop blocking" << std::endl;
      player1->stopBlocking();
    }
  }

  player1->update();

  player2->update();

  player1->printInfo("Player1");
  // player2->printInfo("Player2");
}