#include <stdio.h>

int main()
{
    int n, i, j, k, c=1, range[10][4], nominal[10];
    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter range of each variable: (min max)\n");
    for(i=0;i<n;i++)
    {
	printf("Var %d:\t", i+1);
	scanf("%d %d", &range[i][0], &range[i][3]);
	nominal[i]=(range[i][3]-range[i][0])/2 + range[i][0];
	range[i][1]=range[i][0]+1;
	range[i][2]=range[i][3]-1;
    }

    printf("\nId\t");
    for(i=0; i<n; i++)
	printf("Var %d\t", i+1);
    printf("\n");
    
    printf("%d\t", c++);
    for(i=0; i<n; i++)
	printf("%d\t", nominal[i]);
    printf("\n");
    
    for(i=0; i<n; i++)
    {
	for(k=0; k<4; k++)
	{
	    //Test Case with id c
	    printf("%d\t", c++);
	    for(j=0; j<i; j++)
	    {
		printf("%d\t", nominal[j]);
	    }
	    printf("%d\t", range[i][k]);
	    for(j=i+1; j<n; j++)
	    {
		printf("%d\t", nominal[j]);
	    }
	    printf("\n");
	}	    
    }
    
}
