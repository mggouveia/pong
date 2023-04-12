// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

int main(int argc, char* args[]) {
  int run = 1;
  SDL_Window* window = NULL;
  SDL_Event event;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  atexit(SDL_Quit);

  if ((window = SDL_CreateWindow(
    "Test",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  )) == NULL) {
    printf("could not create window: %s\n", SDL_GetError());
    exit(-1);
  }

  while (run) {
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          run = 0;
          break;
      }
    }

    SDL_Delay(30);
  }

  return 0;
}
