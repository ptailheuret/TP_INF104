#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************** Types **************************/

typedef struct eleve {
  char nom[30];
  char prenom[20];
  int info;
} Eleve_t;

/********************   main   ********************/

int main(int argc, char*argv[]) {
	FILE *fichier;
	//char mot[30];
	char nomfic[80];
	int nmots, i, ret_lec;
	Eleve_t tab_eleves[100];

	printf ("nom du fichier ?\n");
	scanf( "%s", nomfic);

	printf ("nbre de mots a lire ?\n");
	scanf( "%d", &nmots);
	
	/* ouverture du fichier */
	fichier = fopen(nomfic, "r");
	if (fichier == NULL){
		printf("le fichier %s n'existe pas\n", nomfic);
		exit (1);
    }
	
		
	
	/*lire n élèves dans le fichier
	  en les affichant par ligne */

	for (i=0;i<=nmots;i++){
	  ret_lec = fscanf(fichier, "%s %s %d", tab_eleves[i].nom, tab_eleves[i].prenom, &tab_eleves[i].info);
	  printf("Nom = %s \t\t Prenom = %s \t\t Info = %d \n", tab_eleves[i].nom, tab_eleves[i].prenom, tab_eleves[i].info);
	}
	
	return 1;
}
