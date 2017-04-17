#include <stdlib.h>
//-------------------------------------------------
//-----------Header File for Game Board------------
//-------------------------------------------------

//Strucure for each Node of Board
struct Node
{
    int row;	//Store the Row of Node
    int col; 	//Store the Column of Node
    
    char dispChar;    //Displays the current symbol of the Node

    struct Node *right;    //point to the right Node
    struct Node *down;	   //point to the down Node
};

//Creates new Node
//Param row and column integer
// and returns new Node pointer
struct Node *createNewNode(int r, int c)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));	// Allocate Memory for New Node
    temp->row = r;
    temp->col = c;
    temp->dispChar = '.';
    temp->right = NULL;
    temp->down = NULL;

    return temp;
}

//Creates the Game Board
//Returns pointer to the Game Board
struct Node *createBoard()
{
    struct Node *head = NULL;
    head = createNewNode(0, 0);	//first Node
    struct Node *temp = head;
    int i, j, k;
    
    //Creates First Column
    for (i = 1; i < 7; i++)
    {
	temp->down = createNewNode(i, 0);
	temp = temp->down;
    }
    
    //Creates all rows for each column created
    for (i = 0; i < 7; i++)
    { 
	temp = head;
	for (k = 0; k < i; k++)
	    temp = temp->down;	
  	for (j = 1; j < 6; j++)
	{
	    temp->right = createNewNode(i, j);
	    temp = temp->right;
	}
    }
    
    struct Node *node1 = NULL, *node2 = NULL, *nTemp = NULL;
    node1 = head;
    node2 = head->down;
    
    //connects each row to the next row    
    for (i = 0; i < 6; i++)
    {
	temp = node1->right;
	nTemp = node2->right;
	for (j = 1; j < 6; j++)
	{
	    temp->down = nTemp;
	    temp = temp->right;
  	    nTemp = nTemp->right;
	}
	node1 = node1->down;
	node2 = node2->down;
    }
    //Return the Board pointer to the firt Node
    return head;
}

//Displays the current status of Game Board
//Param Struct Node * pointer to head node
void displayBoard(struct Node *head)
{
    struct Node *rowNode = NULL, *colNode = NULL;
    rowNode = head;
    int i, j;
    for (i = 0; i < 7; i++)
    {
        colNode = rowNode;
    	for (j = 0; j < 6; j++)
    	{
    	    printf("%c", colNode->dispChar);
    	    colNode = colNode->right;
    	}
	   printf("\n");
	   rowNode = rowNode->down;
    }
}

//completed boardUpdate function
int boardUpdate(struct Node *head,char symbol,int col)
{
    int i;
    if(col<0||col>5)
        return -1; //Invalid Column No.
    Node *temp = head,*nTemp = NULL;
    while(temp->col != col)
        temp = temp->right; //Finding the column
    if(temp->dispChar != '.')
        return 0; //Column Filled
    //Finding the Node in the column to be updated
    for (i = 0; i < 4; ++i)
    {
        if(temp->down->dispChar != '.')
            {
                temp->dispChar = symbol;
                break;
            }
        temp = temp->down;
    }
    temp->dispChar = symbol; //Updation
    return 1;
}