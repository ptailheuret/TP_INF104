/******************************************************
           synchro avec time-out dans la section critique 

 remarque : ceux qui n'utilisent pas lockf 
 accedent sans controle au fichier.
 Pour verifier, faire une redirection vers ce fichier.

********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include  <signal.h>
#include  <setjmp.h>

#define MAX 5
#define TRUE 1

sigjmp_buf Contexte;
int Ret_lock, Ret_write, Sortie;

int main (int argc, char *argv[]) {
  int  Ret_Sj  ;
  char Tab[256];

  void Traite_Alarme (int Num_Signal);
  
  if (argc != 2) {
      printf(" Utilisation : %s fic_sortie ! \n", argv[0]);
      exit(2);
    }
  
  /*   ......   */ 

  /*-----------------------------------------------------
    sortir sur une fenetre dont ou aura pris le nom 
    avec la commande tty et que l'on passera sur la ligne 
    de commande.
    ----------------------------------------------------- */
  
  if ((Sortie = open (argv[1], O_RDWR)) == -1) {
      perror ("open 2"); 
      exit (1); 
    }
  
  while (TRUE) { 
      /*----------------------------------------------
	Point de reprise sur sortie
	en "time-out" de la SC,
        utiliser sigsetjmp.
        (cf. le man)
	sigsetjmp renvoie 0 ou la valeur que lui a passe siglongjmp
         exemplei : Ret_Sj = sigsetjmp(Contexte,1);
	----------------------------------------------*/ 
      
      /*  ........  */

      
      /*----------------------------------------------
	Verrouillage avant d'entrer dans la SC
	(equivalent d'une operation P sur un semaphore)
	----------------------------------------------*/ 

      /*  ........  */
      
      /*----------------------------------------------
	Debut de section critique
	On ne doit pas y rester plus de MAX secondes
	----------------------------------------------*/ 
   	  /*  ........  */
      while ( fgets(Tab, sizeof(Tab), stdin) ) {
	  if (!strncmp (Tab, "fin", 3)) break;
	  Ret_write = write (Sortie, Tab, strlen(Tab));
	  if (Ret_write  < 0) {
	      printf ("Erreur d'ecriture vers %s\n", argv[1]);
	      break;
	    }
	}   /* fin de la boucle de lecture-ecriture */
      /*----------------------------------------------
	Fin de section critique 
	----------------------------------------------*/ 
   	  /*  ........  */
      /*----------------------------------------------
	Deverrouillage en sortie de la SC
	(equivalent d'une operation V  sur un semaphore)
	----------------------------------------------*/
   	  /*  ........  */  
      printf ("sortie SC, Ret_lock =  %d\n", Ret_lock);

    }  /* fin du while */
}

 
/*----------------------------------------------
 Traite_Alarme
  fonction  de traitement de SIGALRM  :
   1 -  .......
   2 -retour au point de reprise (avant la SC)
      en utilisant siglongjmp
  ----------------------------------------------*/ 

void Traite_Alarme (int Num_Signal) {
	  /*  ........  */   

}
