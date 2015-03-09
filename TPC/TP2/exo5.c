#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  if (argc==3)
    {
      int a = argv[1];
      int b = argv[2];
      printf("a = %d\nb = %d\n",a,b);
      echange(&a,&b);
      printf("a = %d\nb = %d\n",a,b);
    }
  else 
    {
      printf("Entrer 2 arguments");
    }
  return 0;
}




void echange(int *x, int *y)
{
x int tmp;
 tmp = *x;
 *x = *y;
 *y = tmp;
}
