//------------------------------------------------
//----------Header File for Player----------------
//------------------------------------------------

//Structure for Player
struct Player
{
    char name[30];
    char symbol;
};

//Gets Player Info
//Param struct Player pointer, Player Number
void getPlayerInfo (struct Player *p, int playerNum)
{
    char s[30], c;
    printf("Enter Player %d Name\n", playerNum);
    scanf("%s", s);

    if(playerNum==1)
    	c = 'R';
    else
    	c = 'Y';
    strcpy(p->name, s);
    p->symbol = c;
}   
