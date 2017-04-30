#include <SDL2/SDL.h>

//Danger Global Variables
int mouseX = -1, mouseY = -1;

void getMouseState (int *x, int *y)
{
  *x = mouseX;
  *y = mouseY;
}

int handleInput (SDL_Event *e)
{
  if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_GetMouseState(&mouseX, &mouseY);
    return 1;
  }
  else if (e->type == SDL_MOUSEBUTTONUP)
  {
    SDL_GetMouseState(&mouseX, &mouseY);
    return 0;
  }
  return 0;
}
