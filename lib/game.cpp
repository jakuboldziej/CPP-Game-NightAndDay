#include "game.h"
#include "views/pause.h"
#include "views/menu.h"

#include "objects/gameobject.h"
#include "objects/player.h"

Pause *pause = new Pause();
Menu *menu = new Menu();

int Game::windowWidth = 0;
int Game::windowHeight = 0;
SDL_Renderer *Game::renderer = nullptr;

TTF_Font *font = nullptr;

Player *player = nullptr;
GameObject *arrow = nullptr;

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

  char *basePath = SDL_GetBasePath();

  std::string playerPath = std::string(basePath) + "assets/sprites/Samurai/Samurai_Spritelist.png";
  std::string arrowPath = std::string(basePath) + "assets/sprites/Samurai_Archer/Arrow.png";

  player = new Player(playerPath.c_str(), 0, 720 - 128, true);
  arrow = new GameObject(arrowPath.c_str(), 200, 720 - 128, false);

  SDL_free(basePath);

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
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
      gameState = PAUSE;
    }
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
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_SPACE])
    {
      if (!player->isJumping() && player->isOnGround())
        player->jump();
    }
    else if (state[SDL_SCANCODE_A])
    {
      player->move(-1, 0);
      player->play("Run");
      player->flip = SDL_FLIP_HORIZONTAL;
    }
    else if (state[SDL_SCANCODE_D])
    {
      player->move(1, 0);
      player->play("Run");
      player->flip = SDL_FLIP_NONE;
    }
    else
      player->play("Idle");

    player->update();
    arrow->update();
    // player->printInfo("Player");
    // arrow->printInfo("Arrow");
    if (checkCollision(player->getHitbox(), arrow->getHitbox()))
    {
      std::cout << "collision" << std::endl;
    }
  }
}

void Game::render()
{
  SDL_RenderClear(renderer);

  char *basePath = SDL_GetBasePath();
  std::string fontPath = std::string(basePath) + "assets/fonts/vgasyse.fon";
  TTF_Font *font = TTF_OpenFont(fontPath.c_str(), 72);

  SDL_Color white = {255, 255, 255};

  if (gameState == MENU)
  {
    menu->render(font);
  }
  else if (gameState == PLAY)
  {
    player->render();
    arrow->render();

    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
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
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}