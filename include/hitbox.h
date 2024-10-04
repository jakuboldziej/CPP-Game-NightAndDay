struct Hitbox
{
  int width;
  int height;
  int offsetX;
  int offsetY;

  Hitbox() {}
  Hitbox(int w, int h, int oX, int oY)
  {
    width = w;
    height = h;
    offsetX = oX;
    offsetY = oY;
  }
  ~Hitbox() {}
};