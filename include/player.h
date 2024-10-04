#include "gameobject.h"

class Player : public GameObject
{
public:
  Player(const char *textureSheet, int x, int y, bool animated = false, int velocity = 5) : GameObject(textureSheet, x, y, animated, velocity)
  {
    Animation idle = Animation(0, 6, 100);
    Animation walk = Animation(1, 9, 100);
    Animation run = Animation(2, 8, 100);

    animations.emplace("Idle", idle);
    animations.emplace("Walk", walk);
    animations.emplace("Run", run);
  };
  ~Player() {};
};