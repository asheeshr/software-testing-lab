#include <stdio.h>
#include <string.h>
#include <limits.h>

#define SIZE 40
#define CONNECT(x,y) adj_matrix[x][y]=adj_matrix[y][x]=1
#define INCIDENT(n1, n2, e) inc_matrix[n1][e]=inc_matrix[n2][e]=1	

//enum {WHITE, GRAY, BLACK} colors; 

/* Matrix for BFS Traversal */
//colors color[SIZE] = {WHITE, };
int parent[SIZE] = {0, };
int adj_matrix[SIZE][SIZE] = {0, };

int stack[SIZE];
int top=-1;

int make_adj_matrix(FILE *);
void bfs(int n);


int main ()
{
    char filename[50];
    FILE *fp;
    int lines, edges;
    
    printf("Enter the name of the program file: ");
    scanf("%s", filename);
    fp = fopen(filename,"r");

    if(fp==NULL) 
    {
	printf("File not found!");
	return 0;
    }
    
    lines = make_adj_matrix(fp);

    bfs(lines);

    return 0;
}

int make_adj_matrix(FILE *fp)
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

#define ENQUEUE(x) q[++r]=x; f=(f==-1)?0:f;
#define DEQUEUE() q[f++]

void bfs(int n)
{
    int q[SIZE];
    int f=-1,r=-1;
    
    int i,j,u, p=1,t;
    
    parent[1] = 0;
    ENQUEUE(1);
    
    while(f<=r)
    {
	u = DEQUEUE();
	for(j=n; j>=u; j--)
	{
	    if(adj_matrix[u][j]==1)
	    {
		printf("Node %d %d \n", u , j);
		parent[j] = u;
		ENQUEUE(j);
	    }
	    
	    if(j==n && adj_matrix[u][n]) /* Print Path */
	    {
		printf("Path %2d :", p++);
		i=j;
		while(i!=0)
		{
		    printf(" %d", i);
		    i = parent[i];
		}
	    }
		    
	}
	scanf("%c", &t);
    }
    
}
