#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXMOTS 100

/***********   types   ******************/
typedef struct un_mot {
	char texte[30];
	int info;
} Mot_t;

/******  fonctions utilisees   *********/

int lire_fichier(Mot_t *tab, char * texte);
int chercher (char *nom);


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




