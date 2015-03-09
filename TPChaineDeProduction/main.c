#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utils.h"
#include "foncs.h"


/******  variables globales ************/
Mot_t tab_mots[MAXMOTS];


/******  main   **********************/
int main(int argc, char*argv[]){
	char le_fichier[80];
	char un_mot[60];
	int nb_mots, i;
	int trouve;
	
	printf ("nom du fichier ?\n");
	scanf( "%s", le_fichier);
	
	nb_mots = lire_fichier(tab_mots, le_fichier);
	
	/*-- visualisation du tableau a l ecran  ---*/
	for (i=0; i<=nb_mots; i++){
		printf("tab_mots[%d] = %s %d\n", i, tab_mots[i].texte,
			   tab_mots[i].info);		
	}
	
	/*----------------------------------------------
	 Chercher un mot dans le tableau.
	 On reste dans la  boucle 
	 tant qu'on n'a pas tape le mot "fin".
	 ----------------------------------------------*/ 
	while (1){
		printf ("quel mot chercher ?\n");
		scanf("%s", un_mot);
		if (strncmp (un_mot, "fin", 3) == 0) break;
		trouve=chercher (un_mot);
		if (trouve != 0) printf("trouve  %s  %d fois !\n",  un_mot, trouve);
		else printf("pas trouve %s\n",  un_mot);
	}	
return 1;
}





