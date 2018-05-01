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
int move (WindowElem *we, Window *w, Node *head, Player p)
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
  Window w;
  w.window = NULL;
  w.renderer = NULL;

  //Player Info
  Player P1, P2;
  getPlayerInfo(&P1,1);
  getPlayerInfo(&P2,2);

  //Initialising Graphics System
  initSystem(&w);

  // Board Initialization
  Node *board;
  board = createBoard(&w);

  //Graphical Window Elements Structure
  WindowElem we;

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
    std::cout << "P1 " << P1.name << " WON!!!\n";
  else if (result == Y)
    std::cout << "P2 " << P2.name << " WON!!!\n";
  else
    printf("It's a Draw!!!\n");

  //Terminating all Graphics System
  closeSystem(&w);

  return 0;
}
