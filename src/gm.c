#include <stdio.h>
#include <string.h>
#include <limits.h>

#define SIZE 40
#define CONNECT(x,y) gph_matrix[y][x]=edge_name++

int stack[SIZE];
int top=-1;
int gph_matrix[SIZE][SIZE] = {0, };

int make_gph_matrix(FILE *);

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
    
    lines = make_gph_matrix(fp);

    return 0;
}

int make_gph_matrix(FILE *fp)
{
    int c=0, flag=0, temp, edge_name = 'a'-1;
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
    printf("\n");
    printf("     ");
    for(int j=1; j<c+1; j++) /*Print column names*/
	printf(" N%-2d", j);
    printf("\n");
    for(int i=1; i<c+1; i++) 
    {
	printf(" N%-2d ", i); /*Print row names */
	for(int j=1; j<c+1; j++)
	{
	    printf("  %c ", gph_matrix[i][j]==0?' ':gph_matrix[i][j]);
	}
	printf("\n");
    }
    printf("\n");

    return c;
}
