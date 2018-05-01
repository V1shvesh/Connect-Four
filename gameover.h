#include <string>

#define Y -1
#define R 1
#define D 0

//Returns the symbol inside the node of provided coords
char find_val(Node *head,int r,int c)
{
	Node *temp;
	for (int i = 0; i < r; ++i)
	{
		temp = temp->down;
	}
	for(int j = 0;j < c; j++)
	{
		temp = temp->right;
	}
	return temp->color;
}

//Check Column For Win
int findColumn(Node *head,int c)
{
	Node *temp = head;
	char *arr = new char[7];
	for(int i = 0; i < c; i++)
	{
		temp = temp->right;
	}
	for(int j = 0; j < 7; j++)
	{
		arr[j] = temp->color;
		temp = temp->down;
	}
	if(strstr(arr,"RRRR")!=NULL)
		{
			delete [] arr;
			return R;
		}
	if(strstr(arr,"YYYY")!=NULL)
		{
			delete [] arr;
			return Y;
		}
	delete [] arr;
	return 0;
}

//Check Row For Win
int findRow(Node *head, int r)
{
	Node *temp = head;
	char *arr = new char[6];
	for(int i = 0; i < r; i++)
	{
		temp = temp->down;
	}
	for(int j = 0; j < 6; j++)
	{
		arr[j] = temp->color;
		temp = temp->right;
	}
	if(strstr(arr,"RRRR")!=NULL) //Ensure strstr is used properly
		{
			delete [] arr;
			return R;
		}
	if(strstr(arr,"YYYY")!=NULL)
		{
			delete [] arr;
			return Y;
		}
	delete [] arr;
	return 0;
}
int findDiag(Node *head)
{
	int count, arrsize;
	char *arr=NULL;

	// Top-Right Diagonals
	Node *rowN = NULL,*colN = NULL;
	for(int i = 3;i<9;i++)
	{
		arrsize = i < 6 ? i+1 : 12 - i;
		arr = new char[arrsize];
		rowN = head;
		count = 0;
		// printf("Iteration %d--------------------------- \n",arrsize);
		while(rowN != NULL && count < arrsize)
		{
		 	colN = rowN;
			while(colN != NULL)
			{
				// printf("%d,%d ",colN->row,colN->col);
				if(colN->row + colN->col == i)
					break;
				colN = colN->right;
			}
			// printf("\n");
			if(colN!=NULL)
			{
				arr[count] = colN->color;
				count++;
			}
			rowN = rowN->down;

		}
		// printf("\n%s------------------------------------------------\n",arr);
		if(strstr(arr,"RRRR")!=NULL)
		{
			delete [] arr;
			return R;
		}
		if(strstr(arr,"YYYY")!=NULL)
		{
			delete [] arr;
			return Y;
		}

		delete [] arr;
	}

	//Top-Left Diagonals
	Node *cur = NULL;
	for(int i=2;i>=-3;i--)
	{
		cur = head;
		// printf("Iteration %d ---------------------------------------------------\n",i);
		if(i>0)
		{
			for(count = 0;count<i;count++)
				cur = cur->right;
		}
		else
		{
			for(count = 0;count<-i;count++)
				cur = cur->down;
		}
		// printf("cur = (%d,%d)\n",cur->row,cur->col);
		arrsize = i>-1 ? 6 - i : i+7;
		// printf("arrsize = %d\n",arrsize);
		count = 0;
		arr = new char[arrsize];
		while(cur->down!=NULL&&cur->right!=NULL)
		{
			arr[count++] =  cur->color;
			cur = cur->down;
			cur = cur->right;

		}
		arr[count] = cur->color;
		// printf("%s\n",arr);
		if(strstr(arr,"RRRR")!=NULL)
		{
			delete [] arr;
			return R;
		}
		if(strstr(arr,"YYYY")!=NULL)
		{
			delete [] arr;
			return Y;
		}
		delete [] arr;
	}
	return 0;
}

int isGameOver(Node *head)
{
	int i,t;
	for(i=0;i<6;i++)
	{
		if(t=findColumn(head,i))
			return t;
	}
	for(i=0;i<7;i++)
	{
		if(t=findRow(head,i))
			return t;
	}

	if(t=findDiag(head))
			return t;
	return 0;
}
