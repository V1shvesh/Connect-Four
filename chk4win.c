#include <string.h>
#define Y -1
#define R 1
//Strucure for each Node of Board
struct Node
{
    int row;	//Store the Row of Node
    int col; 	//Store the Column of Node
    
    char dispChar;    //Displays the current symbol of the Node

    struct Node *right;    //point to the right Node
    struct Node *down;	   //point to the down Node
};
//Returns the symbol inside the node of provided coords
char find_val(struct Node *head,int r,int c)
{
	int i,j;
	Node *temp;
	for (i = 0; i < r; ++i)
	{
		temp = temp->down;
	}
	for(j = 0;j < c; j++)
	{
		temp = temp->right;
	}
	return temp->dispChar;
}

//Check Column For Win
int fcol(Node *head,int c)
{
	Node *temp = head;
	char *arr = (char *)malloc(7*sizeof(char));
	int i,j;
	for(i=0 i < c;i++)
	{
		temp = temp->right;
	}
	for(j = 0; j < 7; j++)
	{
		arr[j] = temp->dispChar;
		temp = temp->down;
	}
	if(strstr(arr,"RRRR"))
		return 1;
	if(strstr(arr,"YYYY"));
		return -1;
	return 0;
}

//Check Row For Win
int frow(Node *head,int r)
{
	Node *temp = head;
	char *arr = (char *)malloc(7*sizeof(char));
	int i,j;
	for(i=0 i < r;i++)
	{
		temp = temp->down;
	}
	for(j = 0; j < 7; j++)
	{
		arr[j] = temp->dispChar;
		temp = temp->right;
	}
	if(strstr(arr,"RRRR")) //Ensure strstr is used properly
		return R;
	if(strstr(arr,"YYYY"));
		return Y;
	return 0;
}

int chk4win(struct Node *head)
{
	int i,t;
	for(i=0;i<7;i++)
	{
		if(t=fcol(head,i))
			return t;
		if(t=frow(head,i))
			return t;
	}
	return 0;
}