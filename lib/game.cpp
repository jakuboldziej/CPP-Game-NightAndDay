#include "game.h"

#include "views/menu.h"
#include "views/play.h"
#include "views/pause.h"

#include "objects/gameobject.h"
#include "objects/player.h"

Menu *menu;
Play *play;
Pause *pause;

int Game::windowWidth = 0;
int Game::windowHeight = 0;
SDL_Renderer *Game::renderer = nullptr;
char *Game::basePath = nullptr;

TTF_Font *font = nullptr;

Player *player = nullptr;

Game::Game() {};
Game::~Game() {};

void Game::init(const char *title, int xpos, int ypos, bool fullscreen)
{
  int flags = 0;
  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
    windowWidth = 1920;
    windowHeight = 1080;
  }
  else
  {
    windowWidth = 1280;
    windowHeight = 720;
  }

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    SDL_Quit();
  }

  if (TTF_Init() == -1)
  {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    SDL_Quit();
  }

  window = SDL_CreateWindow(title, xpos, ypos, windowWidth, windowHeight, flags);
  if (window)
  {
    std::cout << "Window created!" << std::endl;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer)
  {
    std::cout << "Renderer created!" << std::endl;
  }

  basePath = SDL_GetBasePath();

  std::string playerPath = std::string(basePath) + "assets/sprites/Samurai/Samurai_Spritelist.png";
  std::string arrowPath = std::string(basePath) + "assets/sprites/Samurai_Archer/Arrow.png";

  player = new Player(playerPath.c_str(), 0, 720 - 128, true);

  std::string fontPath = std::string(basePath) + "assets/fonts/vgasyse.fon";
  font = TTF_OpenFont(fontPath.c_str(), 72);
  if (!font)
  {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
  }

  menu = new Menu();
  play = new Play();
  pause = new Pause();

  isRunning = true;
  gameState = MENU;
}

void Game::handleEvents()
{
  SDL_Point mousePosition;
  SDL_Event event;
  SDL_PollEvent(&event);

  if (gameState == MENU)
  {
    menu->handleEvents(mousePosition, event, gameState, isRunning);
  }
  else if (gameState == PLAY)
  {
    play->handleEvents(event, gameState);
  }
  else if (gameState == PAUSE)
  {
    pause->handleEvents(mousePosition, event, gameState);
  }

  if (event.type == SDL_QUIT)
  {
    isRunning = false;
  }
}

void Game::update()
{
  if (gameState == PLAY)
  {
    play->update(player);
  }
}

void Game::render()
{
  SDL_RenderClear(renderer);

  if (gameState == MENU)
  {
    menu->render(font);
  }
  else if (gameState == PLAY)
  {
    play->render(player);
  }
  else if (gameState == PAUSE)
  {
    pause->render(font);
  }

  SDL_RenderPresent(renderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b)
{
  return SDL_HasIntersection(&a, &b);
}

void Game::clean()
{
  if (font)
  {
    TTF_CloseFont(font);
    font = nullptr;
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}