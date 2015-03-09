#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#include <sys/wait.h>
#include <fcntl.h>

#include "semaph.h"

/* Les deux verrous */
sem_t* verrou;
sem_t* verrou_lec;

/* Pour dater les traces  affichees a l'ecran */
struct tm* la_date;
time_t horloge;

/* Descripteur du fichier contennat le compteur partage par les lecteurs */
FILE* fichier;

/* Prototypes des fonctions utilisees */
void lecteur(int le_lecteur);
void ecrivain(int necr);
int premier(int le_lecteur);
int dernier(int le_lecteur);


/********************** main ***********************/
int main(int argc, char *argv[]) {
	int  i, maxecr, maxlec, etat;	
	int compteur = 1;  /* A COMPLETER */
	
	if(argc != 3){
		printf ("utilisation : argv[0] nbre-de-lecteurs  nbre-d-ecrivains!\n");
		exit(1);
 	}
	
	maxlec = atoi(argv[1]);
	maxecr = atoi(argv[2]);
	
	/* creation des semaphores, equivalent de :
	 * Init(verrou, compteur)
	 * Init(verrou_lec, compteur)
	 */
	
	if ((verrou = sem_open(VERROU, O_CREAT, 0644, compteur)) == SEM_FAILED) {
		perror("init verrou commun");
		exit(1);
	}
	
	if ((verrou_lec = sem_open(VERROULEC, O_CREAT, 0644, compteur)) == SEM_FAILED) {
		perror("init verrou Lecteurs");
		exit(1);
	}	
	
	/* Ouverture et initialisation du fichier contenant la
	 * variable partagee par les lecteurs.
	 */
    fichier = fopen(FICLEC, "w+");
    if (fichier == NULL) {
		printf("erreur ouverture\n");
		return 1;       
    }
	fseek(fichier, 0, SEEK_SET);
	fprintf(fichier, "%d", 0);
	fflush(fichier);
	
	/*** Creation des ecrivains ***/
	for (i = 0; i < maxecr ; i++)  {
		if (fork() == 0) ecrivain(i);
	}	
	
	/*** Creation des lecteurs ***/
	for (i = 0; i < maxlec ; i++)  {
		if (fork() == 0) lecteur(i);
	}	
	
	/* Attente de la fin de tous les lecteurs et de tous les ecrivains */
	while (wait(&etat) != -1) 
		printf("main : fin de fils %04x (hexa)\n", etat);
	
	/* Destruction des semaphores */
	sem_close(verrou);
	sem_unlink("VERROU");
	sem_close(verrou_lec);
	sem_unlink("VERROULEC");
	
	printf("main : %s : fin \n", argv[0]);	
	exit(0);
}

/********************** ecrivain  ***********************/
/* Chaque ecrivain execute une boucle de 3 ecritures    */
void ecrivain(int necr){
	int i=0;
	int seconde, minute;
	struct tm  * la_date;
	time_t horloge;
	
	/* initialisation de l horloge */ 
	horloge=time(NULL);
	la_date=localtime(&horloge);
	minute= la_date->tm_min;
	seconde = la_date->tm_sec; 
	
	printf(" ******************** Ecrivain %d Debut :  %02d:%02d\n",  necr, minute, seconde);
	
	/* Boucle d ecriture */
	for (i = 0; i < 3; i++){
		/*  A COMPLETER  */

		
		/* Saisie de la date */
		horloge=time(NULL);
		la_date=localtime(&horloge);
		minute= la_date->tm_min;
		seconde = la_date->tm_sec; 
		printf(" ******************** Ecrivain %d entre SC -- Date :  %02d:%02d (iteration : %d)\n",  necr, minute, seconde,  i);
		
		
		/*****  Debut de la section critique pour les lecteurs et ecrivains *****/
		
		/* Simulation du temps passe a faire des modifications */
		sleep(3+necr%3);
		
		/* Saisie de la date */
		horloge=time(NULL);
		la_date=localtime(&horloge);
		minute= la_date->tm_min;
		seconde = la_date->tm_sec; 
		printf(" ******************** Ecrivain %d va sortir SC  -- Date :  %02d:%02d (iteration : %d)\n",   necr, minute, seconde,  i);
		
		
		/*****  Fin  de la section critique pour les lecteurs et ecrivains *****/
		/*  A COMPLETER  */
	
		sleep(2+i);
	}
	
	printf("Ecrivain %d : fin \n", necr);
	exit(necr);
}

/********************** lecteur  ***********************/
void lecteur(int le_lecteur){
	int seconde, minute;
	
	/*  A COMPLETER  */
	
	if (premier(le_lecteur)) {
		printf("========================= Lecteur %d est le premier ->   \n", le_lecteur);
		/*  A COMPLETER  */
	}

	/*  A COMPLETER  */
	
	/* Saisie de la date */
	horloge=time(NULL);
	la_date=localtime(&horloge);
	minute= la_date->tm_min;
	seconde = la_date->tm_sec;
	
	printf("========================= Lecteur %d dans SC --Date :  %02d:%02d \n", le_lecteur,  minute, seconde);
	
	/*****  Debut  de la section critique pour les lecteurs et ecrivains *****/
	 
	/* Simulation du temps passe en section critique */
	sleep(10+le_lecteur%4);
	
	/* Saisie de la date */
	horloge=time(NULL);
	la_date=localtime(&horloge);
	minute= la_date->tm_min;
	seconde = la_date->tm_sec;
	
	printf("========================= Lecteur %d va sortir de   SC --Date :  %02d:%02d \n", le_lecteur,  minute, seconde);
	
	/*  A COMPLETER  */

	if (dernier(le_lecteur)) {
		printf("========================= Lecteur %d est le dernier ->   \n", le_lecteur);
		
		
		/*****  Fin  de la section critique pour les lecteurs et ecrivains *****/
	/*  A COMPLETER  */;
	}
	

	/*  A COMPLETER  */
	
	exit(le_lecteur);
}

/********************** premier ***********************/
int premier(int le_lecteur){
	int nbre_lecteur, ret_scan;
	int premier  = 0;
	
	/* Lecture du fichier conteanant le nbre de lecteurs */
	fseek(fichier, 0, SEEK_SET);
	ret_scan = fscanf(fichier, "%d", &nbre_lecteur);

	if (nbre_lecteur == 0 ) premier = 1;
	nbre_lecteur++;
	
	fseek(fichier, 0, SEEK_SET);
	fprintf(fichier, "%2d", nbre_lecteur);
	printf("PREM : nbre de lecteurs : %2d\n", nbre_lecteur);
	fflush(fichier);

	
	return premier;	
}


/********************** dernier ***********************/
int dernier(int le_lecteur){
	int nbre_lecteur, ret_scan;
	int dernier = 0;
	
	/* lecture du fichier conteanant le nbre de lecteurs */
	fseek(fichier, 0, SEEK_SET);
	ret_scan = fscanf(fichier, "%d", &nbre_lecteur);

	nbre_lecteur = nbre_lecteur-1;
	if (nbre_lecteur == 0 ) dernier = 1;
	
	fseek(fichier, 0, SEEK_SET);
	fprintf(fichier, "%2d", nbre_lecteur);
	printf("DER : nbre de lecteurs : %2d\n", nbre_lecteur);
	fflush(fichier);
	
	return dernier;
}



