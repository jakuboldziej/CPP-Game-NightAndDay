#define SDL_MAIN_HANDLED
#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils/colors.h"
#include "utils/constants.h"

enum GameState
{
  MENU,
  PLAY,
  PAUSE
};

class Game
{
public:
  Game();
  ~Game();

  void init(const char *title, int xpos, int ypos, bool fullscreen);
  void handleEvents();
  void update();
  void render();
  bool running() { return isRunning; }
  static bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
  void clean();

  static SDL_Renderer *renderer;

  static int windowWidth;
  static int windowHeight;

  static char *basePath;
  static TTF_Font *font;

private:
  bool isRunning = false;
  SDL_Window *window;
  GameState gameState;
};