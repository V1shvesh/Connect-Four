//------------------------------------------------
//----------Header File for Player----------------
//------------------------------------------------

//Structure for Player
struct Player
{
    char name[30];
    int color;
};

//Gets Player Info
//Param struct Player pointer, Player Number
void getPlayerInfo (struct Player *p, int playerNum)
{
    char s[30];
    printf("Enter Player %d Name\n", playerNum);
    scanf("%s", s);

    if(playerNum==1)
    	 p->color = 'R';
    else
    	p->color = 'Y';
    strcpy(p->name, s);
}
