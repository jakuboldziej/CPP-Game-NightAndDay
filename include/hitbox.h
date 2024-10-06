#pragma once

struct Hitbox
{
  int offsetWidth;
  int offsetHeight;
  int offsetX;
  int offsetY;

  Hitbox() {}
  Hitbox(int w, int h, int oX, int oY)
  {
    offsetWidth = w;
    offsetHeight = h;
    offsetX = oX;
    offsetY = oY;
  }
  ~Hitbox() {}
};