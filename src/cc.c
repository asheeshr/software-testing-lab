#include <stdio.h>
#include <string.h>

int source() 
{
    int a, sum = 0;
    char filename[50], buffer[50];
    printf("Enter the name of the program file: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename,"r");
    if (fp==NULL) exit(1);
    while (fgets(buffer, 50, fp)!=NULL) 
    {
	if(strstr(buffer,"if")!=NULL) sum++;
	else if(strstr(buffer,"for")!=NULL) sum++;
	else if(strstr(buffer,"while")!=NULL) sum++;
    }    
    fclose(fp);
    return (sum+1);
}


int e_n() 
{
    int edges = 0, nodes = 0, pNodes=0, sum = 0;
    printf("Enter the number of edges and nodes: ");
    scanf("%d %d",&edges,&nodes);
    printf("Enter the number of predicate nodes: ");
    scanf("%d",&pNodes);
    return edges-nodes+(2*pNodes);
}

int i_areas() 
{
    int areas = 0;
    printf("Enter the number of independent area: ");
    scanf("%d",&areas);
    return areas;
}


int main ()
{
    int c, cc=0;

    printf("Choose method to calculate cyclomatic Complexity: \n");
    printf("\t1.Using source code.\n\t");
    printf("2.Using number of edges and nodes.\n\t");
    printf("3.Using number of independent areas.\n\n");
    scanf("%d",&c);

    switch(c) 
    {
    case 1: cc = source();
	break;
    case 2: cc = e_n();
	break;
    case 3: cc = i_areas();
	break;
    default: printf("Error");
	break;
    }
    printf("The cyclomatic Complexity is %d\n",cc);
    return 0;
}
