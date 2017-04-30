#include "board.h"
#include "player.h"
#include "gameover.h"

//Updates Game Board
int move (struct Window *w, struct Node *head, struct Player p)
{
    int c;
    printf("Enter col num:\n");
    scanf("%d", &c);
    int res = boardUpdate(w, head, p.color, c-1);
    if ( res < 0 )
      printf("Invalid Move\n");
    printBoard(head, w);
    return res;
}

int main (int argc, char **argv)
{
  //Graphical Window Structure
  struct Window w;
  w.window = NULL;
  w.renderer = NULL;

  //Initialising Grahics System
  initSystem(&w);

  // Board Initialization
  struct Node *board;
  board = createBoard(&w);


  printBoard(board, &w);

  //Player Info
	struct Player P1, P2;
	getPlayerInfo(&P1,1);
  getPlayerInfo(&P2,2);


  SDL_Event e;
  int isQuit = 0, moves = 0, result = 0;
  while (!isQuit && (result = isGameOver(board)) == 0 && moves < 42)
  {
    if (moves % 2 == 0)
      moves += move(&w, board, P1);
    else
      moves += move(&w, board, P2);

    printBoard(board, &w);
    moves++;

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
