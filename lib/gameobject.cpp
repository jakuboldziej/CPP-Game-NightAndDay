#include "gameobject.h"
#include "texturemanager.h"

int windowWidth, windowHeight;

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

  if (animated)
  {
    Animation idle = Animation(0, 6, 100);

    animations.emplace("Idle", idle);
  }

  play("Idle");

  srcRect.x = srcRect.y = 0;
  srcRect.w = srcRect.h = 128;
  dstRect.w = srcRect.w;
  dstRect.h = srcRect.h;

  SDL_GetRendererOutputSize(Game::renderer, &windowWidth, &windowHeight);
}

GameObject::~GameObject() {}

void GameObject::render()
{
  TextureManager::draw(texture, srcRect, dstRect, flip);
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
}

void GameObject::move(int dx, int dy)
{
  if (x + dx * velocity < 0 || x + dx * velocity + dstRect.w > windowWidth)
    dx = 0;

  if (y + dy * velocity < 0 || y + dy * velocity + dstRect.h > windowHeight)
    dy = 0;

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
  }
  else
  {
    std::cerr << "Animation not found: " << animName << std::endl;
  }
}

void GameObject::printInfo(const char *name)
{
  std::cout << name << ": x: " << x << " y: " << y << std::endl;
  // std::cout << "srcRect: " << srcRect.x << " " << srcRect.y << " " << srcRect.w << " " << srcRect.h << std::endl;
  std::cout << animations.size() << std::endl;
}