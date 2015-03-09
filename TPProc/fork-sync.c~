#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main () { 
  int valeur, ret_fils,etat ;
  printf ("Je suis le processus pere de pid %d \n", (int)getpid());
  valeur=fork();
  switch (valeur)
    {
    case 0 :
      printf
	("\t\t\t\t********\n\t\t\t\t* FILS *	\n\t\t\t\t********\n");
      printf ("\t\t\t\tProc fils de pid %d \n\t\t\t\tPere de pid %d \n",
	      (int) getpid(),(int) getppid() );
      printf("\t\t\t\tJe vais dormir 30 secondes ...\n");
      sleep (30);
      printf
           ("\t\t\t\tJe me reveille ,\n\t\t\t\tJe termine mon execution par un EXIT(7)\n");
      exit (7);
    case -1:
      printf ("Le fork a echoue");
      exit(2);
    default:
      printf("********\n* PERE *\n********\n"); 
      printf ("Proc pere de pid %d \nFils de pid %d \n",
	      (int) getpid(),valeur );
      printf ("J'attends la fin de mon fils...\n");
      ret_fils = wait (&etat);
      printf 
	("Mon fils de pid %d est termine,\nSon etat etait : %04x\n",
	 ret_fils,etat);
    }
 return 0;
}
