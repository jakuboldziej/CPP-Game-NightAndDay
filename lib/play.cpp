#include "views/play.h"

Button *winnerText;

Play::Play()
{
  buttons["Rematch"] = new Button("text", 0, Game::fullscreen ? 341 * 1.5 : 341, "Rematch", 5, true);
  buttons["Quit"] = new Button("text", 0, Game::fullscreen ? 493 * 1.5 : 493, "Quit", 5, true);
}
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
  if (gameEnded == true)
  {
    winnerText->render();
    buttons["Rematch"]->render(true);
    buttons["Quit"]->render(true);
  }

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
  // Handle game end
  if (gameEnded == true)
    return;

  if (player1->getCurrentHealth() <= 0)
  {
    initGameEnd("Player 2");
    return;
  }
  else if (player2->getCurrentHealth() <= 0)
  {
    initGameEnd("Player 1");
    return;
  }

  // *przenieść keyboard inputy do klasy Player?*
  const Uint8 *state = SDL_GetKeyboardState(nullptr);

  // Player 1

  // Movement
  if (player1->canMove())
  {
    if (state[SDL_SCANCODE_W])
    {
      if (player1->isOnGround())
        player1->jump();
    }
    if (state[SDL_SCANCODE_A])
    {
      player1->move(-1, 0, player2);

      if (player1->isOnGround())
        player1->play("Run");

      player1->flip = SDL_FLIP_HORIZONTAL;
    }
    else if (state[SDL_SCANCODE_D])
    {
      player1->move(1, 0, player2);
      if (player1->isOnGround())
        player1->play("Run");
      player1->flip = SDL_FLIP_NONE;
    }
    else if (player1->isOnGround())
      player1->play("Idle");
  }

  // Attacking
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

  // Blocking
  if (state[SDL_SCANCODE_B] && !player1->isAttacking() && !player1->isJumping())
  {
    if (!player1->isBlocking())
      player1->block();
  }
  else
  {
    if (player1->isBlocking())
    {
      player1->stopBlocking();
    }
  }

  player1->update();
  player1->printInfo("Player1");

  // Player 2

  if (player2->canMove())
  {
    if (state[SDL_SCANCODE_I])
    {
      if (player2->isOnGround())
        player2->jump();
    }
    if (state[SDL_SCANCODE_J])
    {
      player2->move(-1, 0, player1);

      if (player2->isOnGround())
        player2->play("Run");

      player2->flip = SDL_FLIP_HORIZONTAL;
    }
    else if (state[SDL_SCANCODE_L])
    {
      player2->move(1, 0, player1);
      if (player2->isOnGround())
        player2->play("Run");
      player2->flip = SDL_FLIP_NONE;
    }
    else if (player2->isOnGround())
      player2->play("Idle");
  }

  // Attacking
  if (state[SDL_SCANCODE_M])
  {
    if (!player2->isAttacking())
      player2->attack("SwingBackhand");
  }
  else if (state[SDL_SCANCODE_COMMA])
  {
    if (!player2->isAttacking())
      player2->attack("SwingForehand");
  }
  else if (state[SDL_SCANCODE_PERIOD])
  {
    if (!player2->isAttacking())
      player2->attack("SwingDiagonal");
  }

  // Blocking
  if (state[SDL_SCANCODE_SLASH] && !player2->isAttacking() && !player2->isJumping())
  {
    if (!player2->isBlocking())
      player2->block();
  }
  else
  {
    if (player2->isBlocking())
    {
      player2->stopBlocking();
    }
  }

  player2->update();
  // player2->printInfo("Player2");

  // Collision detection
  if (player1->isAttacking() && !player1->attackHit)
  {
    if (Game::checkCollision(player1->getAttackingHitboxes(), player2->getHitbox()))
    {
      player2->takeDamage(20);
      player1->attackHit = true;
    }
  }
  else if (player2->isAttacking() && !player2->attackHit)
  {
    if (Game::checkCollision(player2->getAttackingHitboxes(), player1->getHitbox()))
    {
      player1->takeDamage(20);
      player2->attackHit = true;
    }
  }
}

void Play::initGameEnd(const char *winner)
{
  std::string concatedString = std::string(winner) + " won!";
  winnerText = new Button("text", 0, Game::fullscreen ? 162 * 1.5 : 162, concatedString.c_str(), 6, true);

  gameEnded = true;
}