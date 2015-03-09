#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
  pid_t valeur, valeur1 ;
  printf (" print 1 - Je suis le processus pere num=%d \n",
	  (int)getpid() );
  valeur = fork();
  printf (" print 2 - retour fork: %d - processus num= %d -num pere=%d \n",
	  (int)valeur, (int)getpid(), (int)getppid() );
  valeur1 = fork();
  printf (" print 3 - retour fork: %d - processus num= %d -num pere=%d \n",
	  (int)valeur1, (int)getpid(), (int)getppid() );
  return 0;
}
