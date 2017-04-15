//----------------------------------------------
//-------------Main Source File-----------------
//----------------------------------------------

#include "board.h"
#include "player.h"

//Updates Game Board
//Param struct Player
void move (struct Player p)
{
    int r, c;
    printf("Enter row num:\n");
    scanf("%d", &r);
    printf("Enter col num:\n");
    scanf("%d", &c);
    boardUpdate(p->symbol, r, c);	//To be implemented
}

