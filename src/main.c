// 
// Pong
// 
// 
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


const int WIDTH = 640;
const int HEIGHT = 480;
const int BALL_SIZE = 10;

typedef struct Ball {
  float x;
  float y;
  float xSpeed;
  float ySpeed;
  int size;
} Ball;

Ball ball;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool Initialize(void);
void Update(float);
void Shutdown(void);

Ball MakeBall(int size);
void UpdateBall(Ball *ball, float elapsed);
void RenderBall(const Ball*);


int main(int argc, char* argv[]) {
  srand((unsigned int)time(NULL));

  atexit(Shutdown);  
  
  if (!Initialize()){
    exit(1);
  }

  bool quit = false;
  SDL_Event event;
  
  Uint32 lastTick = SDL_GetTicks();

  while (!quit){
    while (SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
        quit = true;
      }
    }

    Uint32 curTick = SDL_GetTicks();
    Uint32 diff = curTick - lastTick;
    float elapsed = diff / 1000.0f;
    Update(elapsed); // 100 * elapsed
    lastTick = curTick;
  }

  SDL_Quit();
}

bool Initialize(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr,"Failed to initialize SDL: %s\n", 
      SDL_GetError());
    return false;
  }
    
  window = SDL_CreateWindow("Pong",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH,
    HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!window){
    return false;
  }

  ball = MakeBall(BALL_SIZE);

  return true;
}

void Update(float elapsed){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  UpdateBall(&ball, elapsed);
  RenderBall(&ball);

  SDL_RenderPresent(renderer);
}

void Shutdown(void){
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  
  if (window){
    SDL_DestroyWindow(window);
  }
  
  SDL_Quit();
}

bool CoinFlip(void){
  return rand() % 2 == 1 ? true : false;
}
Ball MakeBall(int size){
  const float SPEED = 120;
  Ball ball = {
    .x = WIDTH / 2 - size / 2,
    .y = HEIGHT / 2 - size / 2,
    .size = size,
    .xSpeed = SPEED * (CoinFlip() ? 1 : -1),
    .ySpeed = SPEED * (CoinFlip() ? 1 : -1),
  };
  return ball;
}

void RenderBall(const Ball *ball){
  int size = ball ->size;
  int halfSize = size / 2;
  SDL_Rect rect = {
    .x = ball->x - halfSize,
    .y = ball->y - halfSize,
    .w = size,
    .h = size,
  };
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void UpdateBall(Ball *ball, float elapsed){
  ball->x += ball->xSpeed * elapsed;
  ball->y += ball->ySpeed * elapsed;

  if (ball->x < BALL_SIZE / 2){
    ball->xSpeed = fabs(ball->xSpeed);
  }
  if (ball->x > WIDTH - BALL_SIZE / 2){
    ball->xSpeed = -fabs(ball->xSpeed);
  }
  if (ball->y < BALL_SIZE / 2){
    ball->ySpeed = fabs(ball->ySpeed);
  }
  if (ball->y > HEIGHT - BALL_SIZE / 2){
    ball->ySpeed = -fabs(ball->ySpeed);
  }
}