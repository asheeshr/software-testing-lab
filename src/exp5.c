#include <stdio.h>
#include <stdlib.h>

struct node
{
  char * ptr;
  int n;
} nodes[100];

struct edge
{
  struct node * v1;
  struct node * v2;
  int n1, n2;
} edges[100];

struct node *stack[100];
int top=-1;


int main()
{
  FILE *fptr;
  char *ptr = malloc(sizeof(char)*100);
  size_t *n1 = malloc(sizeof(size_t));
  int i = 0, k = 1;
  *n1 = 100;
  fptr = fopen("./exp5.c", "r");

  edges[0].v1 = NULL;
  edges[0].v2 = NULL;

  while(!feof(fptr))
  {
    getline(&ptr, n1, fptr);
    printf("%s", ptr);
    nodes[i].ptr = ptr;
    nodes[i].n = i;
    
    edges[k].v1 = edges[k-1].v2;
    edges[k].n1 = i-1;

    if(strcmp(ptr, "{")==0)
    {
      if(strstr(nodes[i-1].ptr, "if")!=NULL)
      {
	top++;
	stack[top] = &nodes[i-1];
      }
    }
    else if(strcmp(ptr, "}"))
    {
      if(strstr(stack[top], "if")!=NULL)
      {
	top--;
      }

      

    }
    


    /*    edges[k].v2 = &nodes[i];
    edges[k].n2 = i;*/
    //    printf("e%d : %d - > %d\n", k, edges[k].n1, edges[k].n2);
    i++;
    k++;
  }

  
  /*  for(int j=0; j<i; j++)
  {
    printf("%d :: %s\n", nodes[j].n, nodes[j].ptr);
  }
  
  for(int l=0; l<k; l++)
  {
    printf("e %d : %d - > %d", l, edges[l].v1->n, edges[l].v2->n);
  }
  */

  //  return 0;
}
