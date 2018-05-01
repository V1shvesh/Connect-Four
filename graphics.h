#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 800

struct Window
{
  SDL_Window *window;
  SDL_Renderer *renderer;
};

void printSDLError(std::string errorString)
{
  std::cout << errorString << " : " << SDL_GetError() << "\n";
}

void printIMGError(std::string errorString)
{
  std::cout << errorString << " : " << IMG_GetError() << "\n";
}

void setRectCoordinates(SDL_Rect &r, int x, int y, int w, int h)
{
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
}

//Initialises SDL Graphics API
//return 0 if fails otherwise 1
int initSystem(struct Window *w)
{
  int success = 1;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printSDLError("SDL Initialisation Error");
    success = 0;
  }
  else
  {
    (w)->window = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if ((w)->window == NULL)
    {
      printSDLError("Window Creation Error");
      success = 0;
    }
    else
    {
      (w)->renderer = SDL_CreateRenderer((w)->window, -1, SDL_RENDERER_ACCELERATED);
      if ((w)->renderer == NULL)
      {
        printSDLError("Renderer Creation Error");
        success = 0;
      }
      else
      {
        SDL_SetRenderDrawColor((w)->renderer, 128, 150, 200, 255);

        int imgFlags =  IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
          printSDLError("SDL_IMAGE Initialisation Error");
          success = 0;
        }
      }
    }
  }
}


//Function to Load texture
//Returns the loaded texture
//Param - Path to the Image File
SDL_Texture *loadTexture(std::string path, struct Window *w)
{
  SDL_Texture *nTexture = NULL;
  SDL_Surface *imgSurface = NULL;
  imgSurface = IMG_Load(path.c_str());
  if (imgSurface == NULL)
  {
    printIMGError("Unable To load image at " + path);
    return NULL;
  }
  else
  {
    nTexture = SDL_CreateTextureFromSurface((w)->renderer, imgSurface);
    if(nTexture == NULL)
    {
      printIMGError("Unable To Create Texture Error");
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
