#include "graphics.h"

//structure for each Node of Board
struct Node
{
  int row;
  int col;

  char color;

  //Holds the image file
  SDL_Texture *texture;

  //SDL Rectangle stores positon of the Node
  SDL_Rect rect;

  struct Node *right;
  struct Node *down;
};

//Creates new Node
//Param row and column integer
// and returns new Node pointer
struct Node *createNewNode(int r, int c, struct Window *w)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));	// Allocate Memory for New Node
    temp->row = r;
    temp->col = c;

    temp->color = 'W';
    temp->texture = loadTexture("Images/w.png", w);
    temp->rect.w = SCREEN_WIDTH / 6;
    temp->rect.h = SCREEN_HEIGHT / 7;
    temp->rect.x = (temp->rect.w) * c;
    temp->rect.y = (temp->rect.h) * r;

    temp->right = NULL;
    temp->down = NULL;

    return temp;
}

//Creates the Game Board
//Returns pointer to the Game Board
struct Node *createBoard(struct Window *w)
{
  struct Node *head = NULL;
  head = createNewNode(0, 0, w);	//first Node
  struct Node *temp = head;
  int i, j, k;

  //Creates First Column
  for (i = 1; i < 7; i++)
  {
	  temp->down = createNewNode(i, 0, w);
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
	    temp->right = createNewNode(i, j, w);
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

//Prints the Board
void printBoard(struct Node *head, struct Window *w)
{
  struct Node *rowNode = NULL, *colNode = NULL;
  rowNode = head;
  int i, j;
  SDL_RenderClear(w->renderer);
  for (i = 0; i < 7; i++)
  {
    colNode = rowNode;
    for (j = 0; j < 6; j++)
    {
        SDL_RenderCopy(w->renderer, colNode->texture, NULL, &(colNode->rect));
        colNode = colNode->right;
    }
	  rowNode = rowNode->down;
  }
  rowNode = head;
  for (i = 0; i < 6; i++)
    rowNode = rowNode->down;
  SDL_RenderPresent(w->renderer);
}

//board update function
int boardUpdate(struct Window *w, struct Node *head, char playerColor, int col)
{
    int i;
    if(col < 0 || col > 5)
        return -1; //Invalid Col Num (will give player another chance)

    struct Node *temp = head;

    //Finding the column
    while(temp->col != col)
        temp = temp->right;

    if(temp->color != 'W')
        return -1; //Column Filled (will give player another chance)

    //Finding the Node in the column to be updated
    for (i = 0; i < 6; i++)
    {
        if(temp->down->color != 'W')
        {
          temp->color = playerColor;
          if (playerColor == 'R')
            temp->texture = loadTexture("Images/r.png", w);
          else
            temp->texture = loadTexture("Images/y.png", w);
          break;
        }
        temp = temp->down;
    }

    //Lowest Node of the column
    temp->color = playerColor;
    if (playerColor == 'R')
      temp->texture = loadTexture("Images/r.png", w);
    else
      temp->texture = loadTexture("Images/y.png", w);
    return 0;
}

//TODO Create a flush Board function


//Temporary Main function
/*
int main (int argc, char **argv)
{
  struct Window w;
  w.window = NULL;
  w.renderer = NULL;

  initSystem(&w);

  struct Node *head = createBoard(&w);

  SDL_Event e;
  int isQuit = 0;
  while (!isQuit)
  {
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
    printBoard(head, &w);
  }


  closeSystem(&w);

  return 0;
}
*/
