#pragma once

#include "objects/gameobject.h"

class Player : public GameObject
{
public:
  Player(const char *textureSheet, int x, int y, bool animated = false, float scale = 1, int velocity = 5) : GameObject(textureSheet, x, y, animated, scale, velocity)
  {
    maxHealth = 100;
    currentHealth = maxHealth;

    attackHitboxRect = {0, 0, 0, 0};

    // Animations

    // std::cout << textureSheet << std::endl;
    Animation idle = Animation(0, 6, 100);
    Animation walk = Animation(1, 9, 100);
    Animation run = Animation(2, 8, 100);
    Animation swingBackhand = Animation(3, 4, 100);
    Animation swingForehand = Animation(4, 5, 100);
    Animation swingDiagonal = Animation(5, 4, 100);
    Animation block = Animation(6, 2, 100);
    Animation jump = Animation(7, 9, 100);
    Animation hurt = Animation(8, 3, 100);
    Animation death = Animation(9, 6, 100);

    animations.emplace("Idle", idle);
    animations.emplace("Walk", walk);
    animations.emplace("Run", run);
    animations.emplace("SwingBackhand", swingBackhand);
    animations.emplace("SwingForehand", swingForehand);
    animations.emplace("SwingDiagonal", swingDiagonal);
    animations.emplace("Block", block);
    animations.emplace("Jump", jump);
    animations.emplace("Hurt", hurt);
    animations.emplace("Death", death);

    // Movement hitboxes

    Hitbox idleHitbox = Hitbox(102, 59, 47, 59);
    Hitbox runHitbox = Hitbox(91, 59, 52, 59);

    hitboxSizes.emplace("Idle", idleHitbox);
    hitboxSizes.emplace("Run", runHitbox);
    hitboxSizes.emplace("Jump", idleHitbox);

    // Attacking hitboxes

    Hitbox swingBackhandHitbox = Hitbox(86, 59, 47, 59);
    Hitbox swingDiagonalHitbox = Hitbox(80, 59, 32, 59);

    // dodać osobne hitboxy dla ataków i blokowania
    hitboxSizes.emplace("SwingBackhand", swingBackhandHitbox);
    hitboxSizes.emplace("SwingForehand", swingBackhandHitbox);
    hitboxSizes.emplace("SwingDiagonal", swingDiagonalHitbox);

    hitboxSizes.emplace("Block", idleHitbox);

    attackHitboxMap["SwingBackhand"][0] = Hitbox(0, 0, 0, 0);
    attackHitboxMap["SwingBackhand"][1] = Hitbox(128, 128, 0, 0);
    attackHitboxMap["SwingBackhand"][2] = Hitbox(94, 105, 94, 71);
    attackHitboxMap["SwingBackhand"][3] = Hitbox(94, 105, 94, 71);

    for (auto &hitboxSize : hitboxSizes)
    {
      hitboxSize.second.offsetWidth *= scale;
      hitboxSize.second.offsetHeight *= scale;
      hitboxSize.second.offsetX *= scale;
      hitboxSize.second.offsetY *= scale;
    }

    for (auto &attackType : attackHitboxMap)
    {
      for (auto &frameHitbox : attackType.second)
      {
        frameHitbox.second.offsetWidth *= scale;
        frameHitbox.second.offsetHeight *= scale;
        frameHitbox.second.offsetX *= scale;
        frameHitbox.second.offsetY *= scale;
      }
    }
  }
  ~Player() {}

  void jump() { jumping = true; }
  bool isJumping() { return jumping; }

  bool attackHit = false;
  void attack(const char *pAttackType)
  {
    attackType = pAttackType;
    play(attackType);
    startTime = SDL_GetTicks();
    attacking = true;
  }
  bool isAttacking() { return attacking; }
  SDL_Rect getAttackingHitboxes() { return attackHitboxRect; }

  void block()
  {
    play("Block");
    startTime = SDL_GetTicks();
    blocking = true;
  }
  bool isBlocking() { return blocking; }
  void stopBlocking()
  {

    blocking = false;
  }

  void takeDamage(int damage)
  {
    currentHealth -= damage;
    if (currentHealth < 0)
    {
      currentHealth = 0;
    }
  }

  int getCurrentHealth() { return currentHealth; }
  int getMaxHealth() { return maxHealth; }

  bool canMove() { return !attacking && !blocking; }

  void render()
  {
    GameObject::render();

    // Hitbox
    // SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect(Game::renderer, &hitboxRect);

    // Attack hitbox
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &attackHitboxRect);
  }

  void update()
  {
    if (blocking)
    {
      handleBlocking();
    }
    else if (attacking)
    {
      handleAttacking();
    }
    else
    {
      GameObject::update();

      handleMovement();
    }
  }

  void move(int dx, int dy, Player *otherPlayer)
  {
    SDL_Rect newHitbox = hitboxRect;
    newHitbox.x += dx * velocity;
    newHitbox.y += dy * velocity;

    if (newHitbox.x < 0 || newHitbox.x + newHitbox.w > Game::windowWidth)
      dx = 0;

    if (newHitbox.y < 0 || newHitbox.y + newHitbox.h > Game::windowHeight)
      dy = 0;

    if (Game::checkCollision(newHitbox, otherPlayer->hitboxRect))
    {
      dx = 0;
      dy = 0;
    }

    x += dx * velocity;
    y += dy * velocity;
  }

private:
  bool attacking = false;
  const char *attackType = "";
  bool blocking = false;

  SDL_Rect attackHitboxRect;
  std::map<std::string, std::map<int, Hitbox>> attackHitboxMap;

  bool jumping = false;
  int jumpHeight = hitboxRect.h * 1.2;
  float yVelocity = 0;
  const float gravity = 0.5f;

  int maxHealth;
  int currentHealth;

  void applyGravity()
  {
    if (!isOnGround())
    {
      yVelocity += gravity;
      y += yVelocity;
    }
  }

  void handleBlocking()
  {
    GameObject::update();
  }

  void handleAttacking()
  {
    unsigned int timeElapsed = SDL_GetTicks() - startTime;
    int totalFrames = animations[attackType].frames;
    int animationDuration = totalFrames * animations[attackType].speed;

    if (timeElapsed >= animationDuration)
    {
      attackHitboxRect = {0, 0, 0, 0};
      attacking = false;
      attackHit = false;
    }
    else
    {
      int currentFrame = (timeElapsed / animations[attackType].speed) % totalFrames;

      if (strcmp(attackType, "SwingBackhand") == 0 && attackHitboxMap[attackType][currentFrame].offsetX != 0)
      {
        attackHitboxRect.w = dstRect.w - attackHitboxMap[attackType][currentFrame].offsetWidth;
        attackHitboxRect.h = dstRect.h - attackHitboxMap[attackType][currentFrame].offsetHeight;
        attackHitboxRect.y = dstRect.y + attackHitboxMap[attackType][currentFrame].offsetY;

        if (flip == SDL_FLIP_HORIZONTAL)
          attackHitboxRect.x = dstRect.x + dstRect.w - (dstRect.w - attackHitboxMap[attackType][currentFrame].offsetWidth) - attackHitboxMap[attackType][currentFrame].offsetX;
        else
        {
          attackHitboxRect.x = dstRect.x + attackHitboxMap[attackType][currentFrame].offsetX;
        }
      }

      GameObject::update();
    }
  }

  void handleMovement()
  {
    if (jumping)
    {
      yVelocity += gravity;
      y -= yVelocity;

      if (hitboxRect.y <= Game::windowHeight - jumpHeight)
      {
        jumping = false;
        yVelocity = 0;
      }
    }
    else
      applyGravity();

    if (isOnGround())
      yVelocity = 0;
    else
      play("Jump");
  }
};