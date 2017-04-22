//----------------------------------------------
//-------------Main Source File-----------------
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "player.h"
#include "checkWin.h"

//Updates Game Board
//Param struct Player
int move (struct Node *head,struct Player p)
{
    int c;
    printf("Enter col num:\n");
    scanf("%d", &c);
    int res = boardUpdate(head,p.symbol, c-1);
    if(!res)
    	printf("Invalid Choice!!");
    displayBoard(head);
    return res;
}

int main()
{
	// Board Initialization
	struct Node *board;
	board = createBoard();

	//Player Info
	struct Player P1,P2;
	getPlayerInfo(&P1,1);
	getPlayerInfo(&P2,2);

	// Game loop
	int moves = 0,result = 0;
	displayBoard(board);
	while(!(result = checkWin(board))&&moves<42)
	{
		if(moves%2==0)
			moves += move(board,P1);
		else
			moves += move(board,P2);
	}

	// Result Declaration
	if(!result)
		printf("It's a Draw!!!\n");
	else if(result == 1)
		printf("P1(%s) WON!!!\n",P1.name);
	else
		printf("P2(%s) WON!!!\n",P2.name);

	// Board Deallocation
	flushBoard(board);
	board = NULL;
	return 0;
}