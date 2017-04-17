//----------------------------------------------
//-------------Main Source File-----------------
//----------------------------------------------

#include "board.h"
#include "player.h"

//Updates Game Board
//Param struct Player
void move (struct Player p)
{
    int c;
    printf("Enter col num:\n");
    scanf("%d", &c);
    boardUpdate(p->symbol, c);	//To be implemented
}

