#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define SIZE 50
#define CONNECT(x,y) adj_matrix[x][y]=adj_matrix[y][x]=1
#define INCIDENT(n1, n2, e) inc_matrix[n1][e]=inc_matrix[n2][e]=1

#define TXT_GRE(c) "\x1b[32m" #c "\x1b[m"
#define TXT_BLU(c) "\x1b[34m" #c "\x1b[m"
#define TXT_MAG(c) "\x1b[35m" #c "\x1b[m"
#define TXT_CYA(c) "\x1b[36m" #c "\x1b[m"

int stack[SIZE];
int top=-1;
uint8_t adj_matrix[SIZE][SIZE] = {0, };
uint8_t inc_matrix[SIZE][(SIZE*(SIZE-1))/2] = {0, };
uint8_t drw_matrix[SIZE*2][(SIZE*(SIZE-1))/2] = {0, };

int make_adj_matrix(FILE *);
int make_inc_matrix(int lines);
void draw_pgraph(int l, int e);

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
    
    edges = make_inc_matrix(lines);

    draw_pgraph(lines, edges);
    
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

#ifdef DEBUG
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
#endif

    return c;
}


int make_inc_matrix(int l) //From incidence matrix
{
    int i,j, e=0;
    
    for(i=1;i<l;i++)
    {
	for(j=1;j<l+1;j++)
	{
	    if(adj_matrix[j][j-i]==1) 
	    {
		INCIDENT(j,j-i,e);
		for(int k=j-i+1; k<j; k++) inc_matrix[k][e]=2;
		e++;
	    }
	}
    }

#ifdef DEBUG
    printf("Incidence Matrix (edges %d)::\n", e-1);
    for(i=1; i<l+1; i++)
    {
	for(j=1; j<e; j++)
	{
	    printf("%d ", (inc_matrix[i][j]==2)?2:inc_matrix[i][j]);
	}
	printf("\n");
    }
    printf("\n");
#endif

   return e;
}


void draw_pgraph(int l, int e)
{
    int i,j;
    
    int start, stop, k, flag, mov;
    //Drawing graph
    for(i=1; i<e; i++)
    {
	j=1;
	
	while(inc_matrix[j][i]!=1) j++;
		
	drw_matrix[(j<<1) - 1][i] = '\\';
	drw_matrix[(j<<1)][i] = '|';
	j++;
	
	while(inc_matrix[j][i]==2) 
	{
	    drw_matrix[(j<<1)-1][i]='|';
	    drw_matrix[j<<1][i] = '|';
	    j++;
	}
	
	drw_matrix[(j-1)<<1][i] = '/';
	
    }
    
    //Compacting graph

    for(i=2; i<e; i++)
    {
	j=1;
         	
  	while(drw_matrix[j][i]!='\\') j++;
	start=j;
	while(drw_matrix[j][i]!='/') j++;
	stop=j;

	flag=1;
	mov=0;
	while(flag==1 && i>mov)
	{
	    mov++;
	    for(k=start; k<=stop; k++)
	    {
		if(drw_matrix[k][i-mov]!=0) flag=0;
	    }
	}
	
	for(k=start; k<=stop; k++)
	{
	    drw_matrix[k][i-(mov-1)]=drw_matrix[k][i];
	    drw_matrix[k][i]=0;
	}
	
    }
    
    e-=(mov-1);
    
    for(j=1; j<2*l; j++)
    {
        if(j%2) printf(" "TXT_GRE(*));
	else printf("  ");
        for(i=1; i<e; i++)
	{
	    if(i%3==1) 
		printf(TXT_CYA(%c), (drw_matrix[j][i]==0)?' ':drw_matrix[j][i]);
	    else if(i%3==2) 
		printf(TXT_BLU(%c), (drw_matrix[j][i]==0)?' ':drw_matrix[j][i]);
	    else 
		printf(TXT_MAG(%c), (drw_matrix[j][i]==0)?' ':drw_matrix[j][i]);
	}
	if(j%2) printf("\tN%d", (j>>1)+1);
	printf("\n");
    }
    printf("\n");
    
}
