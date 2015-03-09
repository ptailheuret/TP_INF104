#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) 
{
  int N = 0;
  int i = 0; 
  int fonction(int n);
  int ret;

  if (argc==2)
    {
      N = atoi(argv[1]);
      
      for (i=2;i<N-1;i++)
	{
	  ret = fonction(i);
	  if (ret==1)
	    printf("i=%d",i);
	}
    }

  else 
    {
      printf("Mauvais arguments");
    }
  return 0;
}

int fonction(int n) 

{
  int premier;

  for (premier=2;premier<n-1;premier++) 
    {
      if (n%premier==0)
	return 0;
      
      else if (premier==n)
	return 1;
    }
  return 0;
}
  
