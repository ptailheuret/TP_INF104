#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utils.h"

/********************   lire_fichier   ********************
 lire le fichier mot par mot et le ranger dans le tableau dont
 chaque entree est du type Mot_t 
 **********************************************************/
int lire_fichier(Mot_t *table, char * le_fichier){
	FILE *fichier;
    int ret_lec, nb_mots =0;
	
	fichier = fopen(le_fichier, "r");
	if (fichier == NULL){
		printf("le fichier %s n'existe pas\n", le_fichier);
		exit (1);
	}		
	do{
		ret_lec = fscanf(fichier, "%s", table[nb_mots].texte);
		if (ret_lec > 0)nb_mots++;
		else  
			printf ("ligne  %d : erreur \n", nb_mots);
		
	} while ((ret_lec != EOF) && (nb_mots < MAXMOTS-1) ); 
	
	nb_mots = nb_mots-1;
	return nb_mots;		
}

/********************   chercher   ********************
 chercher un mot dans le tableau tab_mots[]; 
 ******************************************************/
int chercher (char *nom){
	int trouve=0;
	int i;
	for (i=0; i<MAXMOTS; i++){
		if (strcmp(tab_mots[i].texte, nom) == 0){
			trouve=trouve+1;
		}
	}
	return trouve;
}
