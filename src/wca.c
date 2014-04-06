#include <stdio.h>
#include <math.h>

int base5(int n)
{
    int i=1, n5=0;
    while(n!=0)
    {
	n5 += (n%5)*i;
	n = (n - n%5) / 5;
	i*=10;
    }
    return n5;
}


int main()
{
    int n, i, j, k, range[10][5], i5;
    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter range of each variable: (min max)\n");
    for(i=0;i<n;i++)
    {
	printf("Var %d:\t", i+1);
	scanf("%d %d", &range[i][0], &range[i][4]);
	range[i][2]=(range[i][4]-range[i][0])/2 + range[i][0];
	range[i][1]=range[i][0]+1;
	range[i][3]=range[i][4]-1;
    }

    printf("\nId\t");
    for(i=0; i<n; i++)
	printf("Var %d\t", i);
    printf("\n");
    
    for(i=0; i<pow(5,n); i++)
    {
	printf("%d\t", i+1);
	i5 = base5(i);

	for(j=0; j<n; j++)
	{
	    printf("%d\t", range[j][i5%10]);
	    i5/=10;
	}
	printf("\n");
    }
}
