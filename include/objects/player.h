#pragma once

#include "objects/gameobject.h"

class Player : public GameObject
{
public:
  Player(const char *textureSheet, int x, int y, bool animated = false, float scale = 1, int velocity = 5) : GameObject(textureSheet, x, y, animated, scale, velocity)
  {
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

    Hitbox idleHitbox = Hitbox(dstRect.w - 102, dstRect.h - 59, 47, 59);
    Hitbox runHitbox = Hitbox(dstRect.w - 91, dstRect.h - 59, 52, 59);

    hitboxSizes.emplace("Idle", idleHitbox);
    hitboxSizes.emplace("Run", runHitbox);
    hitboxSizes.emplace("Jump", idleHitbox);
  };
  ~Player() {}

  void jump() { jumping = true; }
  bool isJumping() { return jumping; }

  void render()
  {
    // Hitbox
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &hitboxRect);

    GameObject::render();
  }

  void update()
  {
    if (jumping)
    {
      yVelocity += gravity;
      y -= yVelocity;

      // naprawić
      if (y <= Game::windowHeight - srcRect.h - jumpHeight)
      {
        jumping = false;
        yVelocity = 0;
      }
    }
    else
    {
      applyGravity();
    }

    if (isOnGround())
    {
      y = Game::windowHeight - srcRect.h;
      yVelocity = 0;
    }
    else
    {
      play("Jump");
    }

    GameObject::update();
  }

  bool isOnGround()
  {
    // std::cout << y << " " << srcRect.h << " " << scale << " " << Game::windowHeight << std::endl;
    return y + (srcRect.h * scale) >= Game::windowHeight;
  }

private:
  int jumpHeight = srcRect.h;
  bool jumping = false;
  float yVelocity = 0;
  const float gravity = 0.5f;

  void applyGravity()
  {
    if (!isOnGround())
    {
      yVelocity += gravity;
      y += yVelocity;
    }
  }
};