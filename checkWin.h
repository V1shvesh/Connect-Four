#include <string.h>
#define Y -1
#define R 1

//Returns the symbol inside the node of provided coords
char find_val(struct Node *head,int r,int c)
{
	int i,j;
	struct Node *temp;
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
int findColumn(struct Node *head,int c)
{
	struct Node *temp = head;
	char *arr = (char *)malloc(7*sizeof(char));
	int i,j;
	for(i=0; i < c;i++)
	{
		temp = temp->right;
	}
	for(j = 0; j < 7; j++)
	{
		arr[j] = temp->dispChar;
		temp = temp->down;
	}
	if(strstr(arr,"RRRR")!=NULL)
		{
			free(arr);
			return R;
		}
	if(strstr(arr,"YYYY")!=NULL)
		{
			free(arr);
			return Y;
		}
	free(arr);
	return 0;
}

//Check Row For Win
int findRow(struct Node *head,int r)
{
	struct Node *temp = head;
	char *arr = (char *)malloc(6*sizeof(char));
	int i,j;
	for(i=0; i < r;i++)
	{
		temp = temp->down;
	}
	for(j = 0; j < 6; j++)
	{
		arr[j] = temp->dispChar;
		temp = temp->right;
	}
	if(strstr(arr,"RRRR")!=NULL) //Ensure strstr is used properly
		{
			free(arr);
			return R;
		}
	if(strstr(arr,"YYYY")!=NULL)
		{
			free(arr);
			return Y;
		}
	free(arr);
	return 0;
}
int findDiag(struct Node *head)
{
	int i,count,arrsize;
	char *arr=NULL;

	// Top-Right Diagonals
	struct Node *rowN = NULL,*colN = NULL;
	for(i = 3;i<9;i++)
	{
		arrsize = i < 6 ? i+1 : 12 - i;
		arr = (char *)malloc(sizeof(char)*arrsize);
		rowN = head; 
		count = 0;
		// printf("Iteration %d--------------------------- \n",arrsize);
		while(rowN!=NULL&&count<arrsize)
		{
		 	colN = rowN;
			while(colN!=NULL)
			{
				// printf("%d,%d ",colN->row,colN->col);
				if(colN->row+colN->col==i)
					break;
				colN = colN->right;
			}
			// printf("\n");
			if(colN!=NULL)
			{
				arr[count] = colN->dispChar;
				count++;
			}
			rowN = rowN->down;
			
		}
		// printf("\n%s------------------------------------------------\n",arr);
		if(strstr(arr,"RRRR")!=NULL)
		{
			free(arr);
			return R;
		}
		if(strstr(arr,"YYYY")!=NULL)
		{
			free(arr);
			return Y;
		}

		free(arr);
	}
	
	//Top-Left Diagonals
	struct Node *cur = NULL;
	for(i=2;i>=-3;i--)
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
		arr = (char *)malloc(sizeof(char)*arrsize);
		while(cur->down!=NULL&&cur->right!=NULL)
		{
			arr[count++] =  cur->dispChar;
			cur = cur->down;
			cur = cur->right;

		}
		arr[count] = cur->dispChar;
		// printf("%s\n",arr);
		if(strstr(arr,"RRRR")!=NULL)
		{
			free(arr);
			return R;
		}
		if(strstr(arr,"YYYY")!=NULL)
		{
			free(arr);
			return Y;
		}
		free(arr);
	}
	return 0;	
}
int checkWin(struct Node *head)
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
// int checkFull(struct Node *head)
// {
// 	int i;
// 	struct Node *temp = head;
// 	for(i=0;i<6;i++)
// 	{
// 		if(temp->dispChar == '.')
// 		return 0;
// 		temp = temp->right;
// 	}
// 	return 1;
// }