#include "player.h"

Player::Player(const char *textureSheet, int x, int y, int speed) : GameObject(textureSheet, x, y, speed) {}
Player::~Player() {}

void Player::render()
{
  GameObject::render();
}

void Player::update()
{
  GameObject::update();

  // Update the srcRect.x to animate the sprite
  srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 100) % 6);

  std::cout << "srcRect.x: " << srcRect.x << std::endl;
}

void Player::move(int dx, int dy)
{
  GameObject::move(dx, dy);
}

void Player::printInfo(const char *name)
{
  GameObject::printInfo(name);
}