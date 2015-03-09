#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#include <sys/wait.h>
#include <fcntl.h>


#include "barriere.h"

/******************* scenario *****************
init(Sem1, 1); Init(barriere, 0);
{
	P(verrou);
	nb = nb+1;
	if (nb == N){
		nb = nb-1;
		L1 : liberer les processus en attente 
		while(nb > 0){
			V(barriere);
			nb = nb-1;
		}
		V(verrou);
	}
	else {
		V(verrou);
		L2 : attendre 
		P(barriere);
	} 
} 



***************** fin scenario ***************/
 
 /* Les deux semaphores :
 Init(verrou, 1 et  Init(barriere, 0)
 */
sem_t *verrou;     /* verrou */
sem_t *barriere;  /* barriere */

/* Descripteur du fichier contenant le compteur partage par les acteurs */
FILE * fichier;

/* Prototypes des fonctions utilisees */
void acteur(int un_acteur);

int max_acteurs;
int nbre_acteur;

/********************** main ***********************/
int main(int argc, char *argv[]) {
	int  i, etat;	
	
	if(argc != 2){
		printf ("utilisation : argv[0] nbre-de-acteurs  !\n");
		exit(1);
 	}
	
	max_acteurs = atoi(argv[1]);
	
	/* creation et initialisation des semaphores */
	
	
	if ((verrou = sem_open(VERROU, O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("init verrou");
    exit(1);
  }
  
  if ((barriere = sem_open(BARRIERE, O_CREAT, 0644, 0)) == SEM_FAILED) {
    perror("init barriere");
    exit(1);
  }
	
	
	/* Ouverture et initialisation du fichier contenant la
	 * variable partagee par les acteurs.
	 */
    fichier = fopen(FICACTEURS, "w+");
    if (fichier == NULL) {
		printf("erreur ouverture\n");
		return 1;       
    }
	fseek(fichier, 0, SEEK_SET);
	fprintf(fichier, "%d", 0);
	fflush(fichier);
	
	/*** Creation des acteurs ***/
	for (i = 0; i < max_acteurs ; i++)  {
		if (fork() == 0) acteur(i);
	}	
	
	/* Attente de la fin de tous les acteurs  */
	while (wait(&etat) != -1) 
		printf("main : fin de fils %04x (hexa)\n", etat);
	
	/* Destruction des semaphores */
	
	

	sem_close(verrou);
	sem_unlink("VERROU");
	sem_close(barriere);
	sem_unlink("BARRIERE");
  
	
	printf("main : %s : fin \n", argv[0]);	
	exit(0);
}

/********************** acteur  ***********************/

void acteur(int un_acteur)
{
  int ret_scan;
  int seconde, minute;
  struct tm  * la_date;
  time_t horloge;
	
  /* saisie de l horloge */ 
  horloge=time(NULL);
  la_date=localtime(&horloge);
  minute= la_date->tm_min;
  seconde = la_date->tm_sec; 
	
  printf(" ******************** Acteur %d Debut :  %02d:%02d\n",  un_acteur, minute, seconde);
	
  /* Simulation du temps passe pour arriver devant la barriere */
  sleep((un_acteur)%3 +1);
	
  /* P(verrou) */
	
  sem_wait(verrou);
	
  printf("========================= Acteur %d dans SC1 : il a fait P(verrou)\n", un_acteur);
	
  /* Increment du  nbre d acteurs dans le fichier */	
  fseek(fichier, 0, SEEK_SET);
  ret_scan = fscanf(fichier, "%d", &nbre_acteur);
  nbre_acteur++;	
  fseek(fichier, 0, SEEK_SET);
  fprintf(fichier, "%2d", nbre_acteur);
  fflush(fichier);
	
	
  if  (nbre_acteur == max_acteurs ) {
    printf("\n========================= TOUS ARRIVES \n\n");
    sleep(5);
		
    /* Decrement du  nbre d acteurs dans le fichier */	
    fseek(fichier, 0, SEEK_SET);
    ret_scan = fscanf(fichier, "%d", &nbre_acteur);
    nbre_acteur = nbre_acteur-1;		
    fseek(fichier, 0, SEEK_SET);
    fprintf(fichier, "%2d", nbre_acteur);
    fflush(fichier);	
		
    while(nbre_acteur > 0){
      printf("========================= Acteur %d va faire V(barriere) (iteration %d )\n", un_acteur, nbre_acteur);
						
	
      sem_post(barriere);
			
			
      /* Decrement du  nbre d acteurs dans le fichier */	
      fseek(fichier, 0, SEEK_SET);
      ret_scan = fscanf(fichier, "%d", &nbre_acteur);
      nbre_acteur = nbre_acteur-1;		
      fseek(fichier, 0, SEEK_SET);
      fprintf(fichier, "%2d", nbre_acteur);
      fflush(fichier);		
    }
    printf("========================= Acteur %d va sortir de SC1 et faire V(verrou) \n", un_acteur);
		
		
    sem_post(verrou);
		
    ;
  }
  else 
    {
      printf("========================= Acteur %d va sortir de SC1 et faire V(verrou) \n", un_acteur);
		
		
	
      sem_post(verrou);
	
      printf("************ Acteur %d attend devant barriere\n", un_acteur);
		
		
      horloge=time(NULL);
      la_date=localtime(&horloge);
      minute= la_date->tm_min;
      seconde = la_date->tm_sec; 

      sem_wait(barriere);
		
      printf("************ Acteur %d passe la barriere !   %02d:%02d\n",  un_acteur, minute, seconde);
      sleep((un_acteur)%4 +1);

    } 
	
  horloge=time(NULL);
  la_date=localtime(&horloge);
  minute= la_date->tm_min;
  seconde = la_date->tm_sec; 
  printf(" ******************** Acteur %d  : fin  %02d:%02d\n",  un_acteur, minute, seconde);
       
  exit(un_acteur);
}




