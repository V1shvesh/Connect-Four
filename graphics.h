#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 600  //Should be a multiple of 6
#define SCREEN_HEIGHT 700 //Should be a multiple of 7

struct Window
{
  SDL_Window *window;
  SDL_Renderer *renderer;
};

//Initialises SDL Graphics API
//return 0 if fails otherwise 1
int initSystem(struct Window *w)
{
  int success = 1;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("SDL Initialisation Error : %s\n", SDL_GetError());
    success = 0;
  }
  else
  {
    (w)->window = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if ((w)->window == NULL)
    {
      printf("Window Creation Error : %s\n", SDL_GetError());
      success = 0;
    }
    else
    {
      (w)->renderer = SDL_CreateRenderer((w)->window, -1, SDL_RENDERER_ACCELERATED);
      if ((w)->renderer == NULL)
      {
        printf("Renderer Creation Error : %s\n", SDL_GetError());
        success = 0;
      }
      else
      {
        SDL_SetRenderDrawColor((w)->renderer, 0, 128, 255, 255);

        int imgFlags =  IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
          printf("SDL_IMAGE Initialisation Error : %s\n", IMG_GetError());
          success = 0;
        }
      }
    }
  }
}


//Function to Load texture
//Returns the loaded texture
//Param - Path to the Image File
SDL_Texture *loadTexture(char *path, struct Window *w)
{
  SDL_Texture *nTexture = NULL;
  SDL_Surface *imgSurface = NULL;
  imgSurface = IMG_Load(path);
  if (imgSurface == NULL)
  {
    printf("Unable To load image at '%s'\nError : %s\n", path, IMG_GetError());
    return NULL;
  }
  else
  {
    nTexture = SDL_CreateTextureFromSurface((w)->renderer, imgSurface);
    if(nTexture == NULL)
    {
      printf("Unable To Create Texture Error : %s\n", IMG_GetError());
      return NULL;
    }
    SDL_FreeSurface(imgSurface);
  }

  return nTexture;
}

void closeSystem(struct Window *w)
{
  SDL_DestroyRenderer((w)->renderer);
  SDL_DestroyWindow((w)->window);

  IMG_Quit();
  SDL_Quit();
}

//Temporary main function
/*
int main (int argc, char **argv)
{
  struct Window w;
  w.window = NULL;
  w.renderer = NULL;

  initSystem(&w);

  SDL_Texture *t = loadTexture("Images/test.png", &w);

  SDL_Event e;
  int isQuit = 0;
  SDL_RenderClear(w.renderer);
  while (!isQuit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      switch (e.type)
      {
        case SDL_QUIT:
          isQuit = 1;
          break;
        default:
          break;
      }
    }
    SDL_RenderCopy(w.renderer, t, NULL, NULL);
    SDL_RenderPresent(w.renderer);
  }

  SDL_DestroyTexture(t);
  closeSystem(&w);

  return 0;
}
*/
