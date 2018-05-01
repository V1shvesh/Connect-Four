#include <string>

//Structure for Player
struct Player
{
    std::string name;
    int color;
};

//Gets Player Info
//Param struct Player pointer, Player Number
void getPlayerInfo (Player *p, int playerNum)
{
    std::string s;
    std::cout << "Enter Player " << playerNum << " Name\n";
    std::cin >> s;

    if(playerNum==1)
    	 p->color = 'R';
    else
    	p->color = 'Y';
    p->name = s;
}
