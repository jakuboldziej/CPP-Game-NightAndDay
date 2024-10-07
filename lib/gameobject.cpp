#include "objects/gameobject.h"
#include "utils/texturemanager.h"

#include <utility>

GameObject::GameObject(const char *textureSheet, int x, int y, bool animated, float scale, int velocity)
    : x(x), y(y), animated(animated), scale(scale), velocity(velocity)
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

  dstRect.w = srcRect.w * scale;
  dstRect.h = srcRect.h * scale;
  dstRect.x = x;
  dstRect.y = y;

  if (animated)
  {
    Animation idle = Animation(0, 6, 100);

    animations.emplace("Idle", idle);

    Hitbox idleHitbox = Hitbox(102, 59, 47, 59);

    hitboxSizes.emplace("Idle", idleHitbox);

    play("Idle");
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
  SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(Game::renderer, &hitboxRect);
}

void GameObject::update()
{
  if (animated)
  {
    unsigned int timeElapsed = SDL_GetTicks() - startTime;
    int currentFrame = (timeElapsed / frameSpeed) % frames;

    srcRect.x = currentFrame * srcRect.w;
  }
  srcRect.y = animIndex * srcRect.h;

  if (y + dstRect.h > Game::windowHeight)
  {
    y = Game::windowHeight - dstRect.h;
  }

  dstRect.x = x;
  dstRect.y = y;

  if (animated)
  {
    hitboxRect.w = dstRect.w - hitboxSizes[currentAnimation].offsetWidth;
    hitboxRect.h = dstRect.h - hitboxSizes[currentAnimation].offsetHeight;
    hitboxRect.y = dstRect.y + hitboxSizes[currentAnimation].offsetY;

    if (flip == SDL_FLIP_HORIZONTAL)
      hitboxRect.x = dstRect.x + dstRect.w - (dstRect.w - hitboxSizes[currentAnimation].offsetWidth) - hitboxSizes[currentAnimation].offsetX;
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
}

bool GameObject::isOnGround()
{
  return y + dstRect.h == Game::windowHeight;
}

void GameObject::play(const char *animName)
{
  if (animations.find(animName) != animations.end())
  {
    if (currentAnimation != animName)
    {
      animIndex = animations[animName].index;
      srcRect.x = 0;
      startTime = SDL_GetTicks();
    }

    Animation anim = animations[animName];
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
  // std::cout << "|" << name << "| " << "x: " << x << " y: " << y << std::endl;
  // std::cout << "|" << name << "| " << "srcRect - x: " << srcRect.x << " y: " << srcRect.y << " w: " << srcRect.w << " h: " << srcRect.h << std::endl;
  // std::cout << "|" << name << "| " << "dstRect - x: " << dstRect.x << " y: " << dstRect.y << " w: " << dstRect.w << " h: " << dstRect.h << std::endl;
  // std::cout << "|" << name << "| " << "hitboxRect - x: " << hitboxRect.x << " y: " << hitboxRect.y << " w: " << hitboxRect.w << " h: " << hitboxRect.h << std::endl;
  // std::cout << "|" << name << "| " << isOnGround() << std::endl;
  // std::cout << "|" << name << "| " << "windowWidth: " << Game::windowWidth << " windowHeight: " << Game::windowHeight << std::endl;
}