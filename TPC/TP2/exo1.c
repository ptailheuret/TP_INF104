#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
  int entier = 0;
  float reel = 0.0;
  if (argc==3) 
    {
      entier=atoi(argv[1]);
      reel=atof(argv[2]);
      printf("entier = %d et reel = %f\n", entier, reel);
    }
  return 0;
}
