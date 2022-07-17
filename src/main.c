#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL2/SDL.h>
#include <stdbool.h>

void handle_events(void);
void loop(void);
void quit_game(void);

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;

bool running = false;

bool init(void)
{
  bool success = true;
  window = NULL;
  renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not be initiliazed. SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if (!window)
  {
    printf("SDL_Window could not be initialized. SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  }

  running = true;
  return success;
}

int main()
{
  if (!init())
    return -1;
  else
  {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#endif
#ifndef __EMSCRIPTEN__
    while (running)
      loop();
#endif
  }

  quit_game();
  return 0;
}

void loop()
{
  handle_events();

  SDL_SetRenderDrawColor(renderer, 18, 1, 54, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);

  SDL_Delay(70);
}

void handle_events()
{
  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      quit_game();
    }
  }
}

void quit_game(void)
{
  SDL_DestroyWindow(window);
  window = NULL;

  SDL_DestroyRenderer(renderer);
  renderer = NULL;

  SDL_Quit();

  running = false;

#ifdef __EMSCRIPTEN__
  emscripten_cancel_main_loop();
#endif
}
