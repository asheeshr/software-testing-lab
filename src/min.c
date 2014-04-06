#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_LENGTH 100

int min(int arr[], int len)
{
  int min=INT_MAX, i;
  for(i=0; i<len; i++) min = min>arr[i]?arr[i]:min;
  return min;
}


int input(int arr[], int min_range[], int max_range[])
{
  int len, i;
  printf("Enter length: ");
  if(scanf("%d", &len)!=1) /*Validate length*/
  {
    printf("Invalid input!\n");
    exit(0);
  }

  /*printf("Length = %d\n", len);*/
  for(i=0; i<len; i++)
  {  
    printf("Enter min and max of %d number: ", i+1);
    if(scanf("%d", min_range+i)!=1 || min_range[i]<INT_MIN || min_range[i]>INT_MAX)
      {
	printf("Invalid input!\n");
	exit(0);
      }
    if(scanf("%d", max_range+i)!=1 || max_range[i]<INT_MIN || max_range[i]>INT_MAX)
      {
	printf("Invalid input!\n");
	exit(0);
      }
  }

  
  for(i=0; i<len; i++)
  {  
    printf("Enter %d number :", i+1);
    if(scanf("%d", arr+i)!=1 || arr[i]<min_range[i] || arr[i]>max_range[i])
      {
	printf("Invalid input!\n");
	exit(0);
      }
  }

  return len;
}

int main()
{
  int arr[MAX_LENGTH], len = 3, min_range[MAX_LENGTH], max_range[MAX_LENGTH];
  
  /* Take inputs and print minimum */
  len = input(arr, min_range, max_range);
  printf("Minimum = %d \n", min(arr, len));
  
  return 0;
}
