#include "graphics.h"

struct WindowElem
{
  SDL_Texture *banner;
  SDL_Rect bannerRect;

  SDL_Texture *turnTexture;
  SDL_Rect turnLeftRect, turnRightRect;
};

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

  Node *right;
  Node *down;
};

//Creates new Node
//Param row and column integer
// and returns new Node pointer
Node *createNewNode(int r, int c, Window *w)
{
    Node *temp = new Node;	// Allocate Memory for New Node
    temp->row = r;
    temp->col = c;

    temp->color = 'W';
    temp->texture = loadTexture("Images/w.png", w);
    temp->rect.w = (SCREEN_WIDTH - 100) / 6;
    temp->rect.h = (SCREEN_HEIGHT - 100) / 7;
    temp->rect.x = (temp->rect.w) * c + 50;
    temp->rect.y = (temp->rect.h) * r + 100;

    temp->right = NULL;
    temp->down = NULL;

    return temp;
}

//Creates the Game Board
//Returns pointer to the Game Board
Node *createBoard(Window *w)
{
  Node *head = NULL;
  head = createNewNode(0, 0, w);	//first Node
  Node *temp = head;

  //Creates First Column
  for (int i = 1; i < 7; i++)
  {
	  temp->down = createNewNode(i, 0, w);
	  temp = temp->down;
  }

  //Creates all rows for each column created
  for (int i = 0; i < 7; i++)
  {
	  temp = head;
	  for (int k = 0; k < i; k++)
	    temp = temp->down;
    for (int j = 1; j < 6; j++)
	  {
	    temp->right = createNewNode(i, j, w);
	    temp = temp->right;
	  }
  }

  Node *node1 = NULL, *node2 = NULL, *nTemp = NULL;
  node1 = head;
  node2 = head->down;

  //connects each row to the next row
  for (int i = 0; i < 6; i++)
  {
	  temp = node1->right;
	  nTemp = node2->right;
	  for (int j = 1; j < 6; j++)
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

//Initialisation of Main Window Textures
void mainWindowInit(WindowElem *we, Window *w)
{
  we->banner = loadTexture("Images/banner.png", w);
  setRectCoordinates(we->bannerRect, 0, 0, 700, 100);

  we->turnTexture = loadTexture("Images/redTurn.png", w);
  setRectCoordinates(we->turnLeftRect, 0, 100, 50, 700);
  setRectCoordinates(we->turnRightRect, SCREEN_WIDTH - 10, 100, 50, 700);
}

//Prints the Board
void printBoard(Node *head, Window *w, WindowElem *we)
{
  Node *rowNode = NULL, *colNode = NULL;
  rowNode = head;

  //Clear Screen
  SDL_RenderClear(w->renderer);

  //Print Banner
  SDL_RenderCopy(w->renderer, we->banner, NULL, &(we->bannerRect));

  //Print The Turn Texture
  SDL_RenderCopy(w->renderer, we->turnTexture, NULL, &(we->turnLeftRect));
  SDL_RenderCopy(w->renderer, we->turnTexture, NULL, &(we->turnRightRect));

  //Print The Board
  for (int i = 0; i < 7; i++)
  {
    colNode = rowNode;
    for (int j = 0; j < 6; j++)
    {
        SDL_RenderCopy(w->renderer, colNode->texture, NULL, &(colNode->rect));
        colNode = colNode->right;
    }
	  rowNode = rowNode->down;
  }
  rowNode = head;
  for (int i = 0; i < 6; i++)
    rowNode = rowNode->down;
  SDL_RenderPresent(w->renderer);
}

//board update function
int boardUpdate(struct WindowElem *we, Window *w, Node *head, char playerColor, int col)
{
    if(col < 0 || col > 5)
        return -1; //Invalid Col Num (will give player another chance)

    Node *temp = head;

    //Finding the column
    while(temp->col != col)
        temp = temp->right;

    if(temp->color != 'W')
        return -1; //Column Filled (will give player another chance)

    //Finding the Node in the column to be updated
    for (int i = 0; i < 6; i++)
    {
        if(temp->down->color != 'W')
        {
          temp->color = playerColor;
          if (playerColor == 'R')
          {
              temp->texture = loadTexture("Images/r.png", w);
              we->turnTexture = loadTexture("Images/yellowTurn.png", w);  //Change Turn Texture
          }
          else
          {
              temp->texture = loadTexture("Images/y.png", w);
              we->turnTexture = loadTexture("Images/redTurn.png", w); //Change Turn Texture
          }
          break;
        }
        temp = temp->down;
    }

    //Lowest Node of the column
    temp->color = playerColor;
    if (playerColor == 'R')
    {
      temp->texture = loadTexture("Images/r.png", w);
      we->turnTexture = loadTexture("Images/yellowTurn.png", w);
    }
    else
    {
      temp->texture = loadTexture("Images/y.png", w);
      we->turnTexture = loadTexture("Images/redTurn.png", w);
    }
    return 0;
}

//TODO Create a flush Board function
