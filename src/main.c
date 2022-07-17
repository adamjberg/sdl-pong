#include <SDL2/SDL.h>

int main()
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Pong",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640,
                                        480,
                                        SDL_WINDOW_OPENGL);

  while (1)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        // Break out of the loop on quit
        break;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}