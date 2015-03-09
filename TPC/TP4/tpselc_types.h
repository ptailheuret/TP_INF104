/****************** Types **************************/

typedef struct eleve {
  char nom[30];
  char prenom[20];
  int info;
} Eleve_t;

typedef struct maillon{
      Eleve_t  eleve;
      struct maillon * suivant;
} Maillon_t;
