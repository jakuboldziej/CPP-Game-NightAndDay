#include "objects/gameobject.h"
#include "utils/texturemanager.h"

#include <utility>

GameObject::GameObject(const char *textureSheet, int x, int y, bool animated, float scale, int velocity)
    : x(x), y(y - (gameObjectRes * scale)), animated(animated), scale(scale), velocity(velocity)
{
  try
  {
    texture = TextureManager::loadTexture(textureSheet);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  if (texture == nullptr)
  {
    std::cerr << "Failed to load texture: " << textureSheet << std::endl;
    return;
  }

  srcRect.x = srcRect.y = 0;
  srcRect.w = srcRect.h = gameObjectRes;

  // naprawić skalowanie się
  dstRect.w = srcRect.w * scale;
  dstRect.h = srcRect.h * scale;
  dstRect.x = x;
  dstRect.y = y;

  if (animated)
  {
    Animation idle = Animation(0, 6, 100);

    animations.emplace("Idle", idle);
  }

  hitboxRect = dstRect;
}

GameObject::~GameObject()
{
  if (texture)
  {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
}

void GameObject::render()
{
  TextureManager::draw(texture, srcRect, dstRect, flip);

  // Hitbox
  // SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
  // SDL_RenderDrawRect(Game::renderer, &hitboxRect);
}

void GameObject::update()
{
  if (animated)
  {
    int currentFrame = (SDL_GetTicks() / frameSpeed) % frames;
    srcRect.x = currentFrame * srcRect.w;
  }
  srcRect.y = animIndex * srcRect.h;

  dstRect.x = x;
  dstRect.y = y;

  if (animated)
  {
    hitboxRect.y = dstRect.y + hitboxSizes[currentAnimation].offsetY;
    hitboxRect.w = hitboxSizes[currentAnimation].width;
    hitboxRect.h = hitboxSizes[currentAnimation].height;

    if (flip == SDL_FLIP_HORIZONTAL)
      hitboxRect.x = dstRect.x + dstRect.w - hitboxSizes[currentAnimation].width - hitboxSizes[currentAnimation].offsetX;
    else
      hitboxRect.x = dstRect.x + hitboxSizes[currentAnimation].offsetX;
  }
  else
  {
    hitboxRect = dstRect;
  }
}

void GameObject::move(int dx, int dy)
{
  if (hitboxRect.x + dx * velocity < 0 || hitboxRect.x + dx * velocity + hitboxRect.w >= Game::windowWidth)
    dx = 0;

  x += dx * velocity;
  y += dy * velocity;
}

void GameObject::play(const char *animName)
{
  if (animations.find(animName) != animations.end())
  {
    Animation anim = animations[animName];
    animIndex = anim.index;
    frames = anim.frames;
    frameSpeed = anim.speed;

    currentAnimation = animName;
  }
  else
  {
    std::cerr << "Animation not found: " << animName << std::endl;
  }
}

void GameObject::printInfo(const char *name)
{
  // std::cout << "|" << name << "| " << ": x: " << x << " y: " << y << std::endl;
  // std::cout << "|" << name << "| " << "srcRect - x: " << srcRect.x << " y: " << srcRect.y << " w: " << srcRect.w << " h: " << srcRect.h << std::endl;
  std::cout << "|" << name << "| " << "hitboxRect - x: " << hitboxRect.x << " y: " << hitboxRect.y << " w: " << hitboxRect.w << " h: " << hitboxRect.h << std::endl;
  // std::cout << "|" << name << "| " << animations.size() << std::endl;
  // std::cout << "|" << name << "| " << y << " " << srcRect.h << " " << Game::windowHeight << std::endl;
}