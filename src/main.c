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

const int screen_height = 400;
const int screen_width = 720;

SDL_Rect ball;
const int ball_size = 14;
const int half_ball_size = ball_size / 2;
int ball_speed = 1;
int ball_x_direction = 1;
int ball_y_direction = 1;

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

  window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
  if (!window)
  {
    printf("SDL_Window could not be initialized. SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  }

  ball.x = (screen_width / 2) - half_ball_size;
  ball.y = (screen_height / 2) - half_ball_size;
  ball.h = ball_size;
  ball.w = ball_size;

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

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  ball.x += ball_speed * ball_x_direction;
  ball.y += ball_speed * ball_y_direction;

  if (ball.x <= 0) {
    ball_x_direction = 1;
  } else if (ball.x + ball_size >= screen_width) {
    ball_x_direction = -1;
  }

  if (ball.y <= 0) {
    ball_y_direction = 1;
  } else if (ball.y + ball_size >= screen_height) {
    ball_y_direction = -1;
  }

  SDL_RenderFillRect(renderer, &ball);

  SDL_RenderPresent(renderer);
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
