#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


#include "tpselc-types.h"
#include "gere-liste.h"

/***************************************************
RAPPEL :
typedef struct Eleve {
	char Nom[20];
	char Prenom[20];
	char login[20];
	char photo[20];
	int x, y, z;
} Eleve_t;
*****************   globales   ********************/

Maillon_t * debut = NULL;

/********************   main   ********************/
int main(int argc, char*argv[]) {
  char nomfic[80];
  int i=0, ilig;
  Eleve_t tab_eleves[100];
  int lire_fichier(Eleve_t *table, char * nomfic);
  
  printf ("nom du fichier ?\n");
  scanf( "%s", nomfic);
  
  /****** lire le fichier et le ranger dans le tableau  *******/
  ilig = lire_fichier(tab_eleves, nomfic);
  printf("Nombre de lignes = %d\n",ilig);
  
  /****** visualisation du tableau a l ecran  *******/
  while(1){
    printf("Nom = %s \t\t Prenom = %s \t\t Info = %d \n", tab_eleves[i].nom, tab_eleves[i].prenom, tab_eleves[i].info);
    i++;
    if(i>=100)
      break;
  }
  
  
  // on cree une liste chainee a partir du tableau
  for (i = 0; i <=dimtab; i++){
    debut = chainer(debut, nouveau_maillon( tab_eleves[i]) );
    
    ecrire_liste(debut);
    
    ecrire_fic_liste(debut, argv[1]);
    
    
    return 0;
}
/********************   lire_fichier   ********************
* lire le fichier ligne par ligne et le ranger dans le tableau dont
* chaque entree est du type Eleve_ti.
* Renvoie le nombre de lignes lues.
**************************************************************/

int lire_fichier(Eleve_t *table, char * nomfic){
  FILE *fichier;
  int ret_lec,ilig =0;
  int i=0;

  fichier = fopen(nomfic, "r");
  if (fichier == NULL){
    printf("le fichier %s n'existe pas\n", nomfic);
    exit (1);
  }
  
  while(1){
    ret_lec = fscanf(fichier, "%s %s %d", table[i].nom, table[i].prenom, &table[i].info);
    i++;
    ilig++;
    if (i>=100)
      break;
  }
  
  return ilig;		
}
