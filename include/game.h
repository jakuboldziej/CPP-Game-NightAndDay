#define SDL_MAIN_HANDLED
#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

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
  void clean();
  bool running() { return isRunning; }

  static SDL_Renderer *renderer;

  int windowWidth = 1280;
  int windowHeight = 720;

private:
  int count = 0;
  bool isRunning = false;
  SDL_Window *window;
  GameState gameState;
};