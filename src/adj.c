#include <stdio.h>
#include <string.h>
#include <limits.h>

#define SIZE 40
#define CONNECT(x,y) adj_matrix[x][y]=adj_matrix[y][x]=1
#define INCIDENT(n1, n2, e)				\
//    {							\
    inc_matrix[n1][e]=inc_matrix[n2][e]=1;		//	\
//	for(int k=n1+1; k<n2; k++) inc_matrix[k][e]=2;	\
//    }

int stack[SIZE];
int top=-1;
int adj_matrix[SIZE][SIZE] = {0, };
int inc_matrix[SIZE][(SIZE*(SIZE-1))/2] = {0, };

int make_matrix(FILE *);
void draw_matrix(int lines);

int main ()
{
    char filename[50];
    FILE *fp;
    int lines;
    
    printf("Enter the name of the program file: ");
    scanf("%s", filename);
    fp = fopen(filename,"r");

    if(fp==NULL) 
    {
	printf("File not found!");
	return 0;
    }
    
    lines = make_matrix(fp);
    
    draw_matrix(lines);

    return 0;
}

int make_matrix(FILE *fp)
{
    int c=0, flag=0, temp;
    char buffer[50];

    while(fgets(buffer, 50, fp)!=NULL) 
    {
	c++;
	if(flag>0)
	{
	    if(strstr(buffer,"else")!=NULL && strstr(buffer,"{")!=NULL)
	    {
//		printf("W1 Top : %d\n", top);
		temp=stack[top--];
		CONNECT(c,temp);
		stack[++top]=c-1;
		flag--;
		continue;
	    }
	    else if(strstr(buffer,"if")==NULL && strstr(buffer, "else")==NULL)
	    {
//		printf("W2 Top : %d\n", top);
		temp=stack[top--];
		CONNECT(c,temp);
		CONNECT(c,c-1);
		flag--;
		continue;
	    }
	}
	
	if(strstr(buffer,"if")!=NULL && strstr(buffer, "{")!=NULL)
	{
	    stack[++top] = c;
//	    printf("C2 Top : %d\n", top);
	}
	else if(strstr(buffer, "}")!=NULL)
	{
	    flag++;
	}
	else
	{
	}
	
	CONNECT(c,c-1);
    }    
    fclose(fp);

    printf("Adjacency Matrix::\n");
    for(int i=1; i<c+1; i++)
    {
	for(int j=1; j<c+1; j++)
	{
	    printf("%d ", adj_matrix[i][j]);
	}
	printf("\n");
    }
    printf("\n");

    return c;
}


void draw_matrix(int l)
{
    int i,j, e=0;
    //Create channels for edges
    
    for(i=1;i<l+1;i++)
    {
	for(j=i; j>0; j--)
	{
	    if(adj_matrix[i][j]) 
	    {
		INCIDENT(i,j,e);
		for(int k=i+1; k<j; k++) inc_matrix[k][e]=2;
		e++;
	    }
	}
    }

    printf("Incidence Matrix (edges %d)::\n", e);
    for(i=1; i<l+1; i++)
    {
	for(j=1; j<e; j++)
	{
	    printf("%d ", inc_matrix[i][j]);
	}
	printf("\n");
    }
    printf("\n");

    //Draw each channel
    
}
