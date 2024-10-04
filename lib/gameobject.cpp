#include "gameobject.h"
#include "texturemanager.h"

GameObject::GameObject(const char *textureSheet, int x, int y, bool animated, int velocity)
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

  this->x = x;
  this->y = y;
  this->velocity = velocity;
  this->animated = animated;

  srcRect.x = srcRect.y = 0;
  srcRect.w = srcRect.h = 128;

  dstRect.w = srcRect.w;
  dstRect.h = srcRect.h;
  dstRect.x = x;
  dstRect.y = y;

  if (animated)
  {
    Animation idle = Animation(0, 6, 100);

    animations.emplace("Idle", idle);
    play("Idle");
  }
}

GameObject::~GameObject() {}

void GameObject::render()
{
  TextureManager::draw(texture, srcRect, dstRect, flip);

  // Hitbox
  SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(Game::renderer, &hitboxRect);
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

  hitboxRect.x = dstRect.x;
  hitboxRect.y = dstRect.y;
}

void GameObject::move(int dx, int dy)
{
  if (hitboxRect.x + dx * velocity < 0 || hitboxRect.x + dx * velocity + hitboxRect.w > Game::windowWidth)
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

    if (hitboxSizes.find(animName) != hitboxSizes.end())
    {
      hitboxRect.w = hitboxSizes[animName].width;
      hitboxRect.h = hitboxSizes[animName].height;
      hitboxRect.x = hitboxSizes[animName].offsetX;
      hitboxRect.y = hitboxSizes[animName].offsetY;
    }
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