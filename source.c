#include "board.h"
#include "player.h"
#include "input.h"
#include "gameover.h"

int getColumn (int x, int y)
{
  if (x < 50 || x > SCREEN_WIDTH - 50 || y < 100 || y > SCREEN_HEIGHT)
    return 0;
  return ((x - 50) / ((SCREEN_WIDTH - 100) / 6)) + 1;
}

//Updates Game Board
int move (struct WindowElem *we, struct Window *w, struct Node *head, struct Player p)
{
    int c, x, y;
    getMouseState(&x, &y);
    c = getColumn(x, y);
    int res = boardUpdate(we, w, head, p.color, c-1);
    return res;
}

int main (int argc, char **argv)
{
  //Graphical Window Structure
  struct Window w;
  w.window = NULL;
  w.renderer = NULL;

  //Player Info
  struct Player P1, P2;
  getPlayerInfo(&P1,1);
  getPlayerInfo(&P2,2);

  //Initialising Graphics System
  initSystem(&w);

  // Board Initialization
  struct Node *board;
  board = createBoard(&w);

  //Graphical Window Elements Structure
  struct WindowElem we;

  //Main Window Elements Initialization
  mainWindowInit(&we, &w);

  printBoard(board, &w, &we);

  //Main Game Loop
  SDL_Event e;
  int isQuit = 0, moves = 0, result = 0, isMousePressed = 0;
  while (!isQuit && (result = isGameOver(board)) == 0 && moves < 42)
  {
    if (SDL_PollEvent(&e) != 0)
    {
      switch (e.type)
      {
        case SDL_QUIT:
          isQuit = 1;
          break;
        default:
          break;
      }
      isMousePressed = handleInput(&e);
    }
    if (isMousePressed)
    {
      if (moves % 2 == 0)
        moves += move(&we, &w, board, P1);
      else
        moves += move(&we, &w, board, P2);
      isMousePressed = 0;
      moves++;
    }
    printBoard(board, &w, &we);
  }

  if (result == R)
    printf("P1(%s) WON!!!\n",P1.name);
  else if (result == Y)
    printf("P2(%s) WON!!!\n",P2.name);
  else
    printf("It's a Draw!!!\n");

  //Terminating all Graphics System
  closeSystem(&w);

  return 0;
}
