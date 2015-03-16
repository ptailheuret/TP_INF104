/*************************************
Recuperation des erreurs d adressage :
Traitement special pour les siagnaux
SIGSEGV
et
SIGBUS
*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

long Tab_Index, Tab[100];
jmp_buf contexte;

/**************************************/
/* main                               */
/**************************************/
int main(int argc, char *argv[]) {
	long Retour, Ret_scan;
	void Traite_Sig(int Numero);
	
	for (Tab_Index=0 ; Tab_Index<100; Tab_Index++)
	  Tab[Tab_Index]= Tab_Index;
	
	/* reperer les adresses */
	printf ("Tab = (hexa)%p, adresse Tab[0] = %p, adresse Tab[99] = %p\n",Tab , &Tab[0], &Tab[99]);
	
	/*  Associer la fonction de traitement aux signaux */

	//SIGBUS
	Retour = (long)signal(7 ,Traite_Sig);
	printf ("retour de signal (hexa): %lx\n", Retour);

	//SIGSEGV
	Retour =(long)signal(11 ,Traite_Sig);
	printf ("retour de signal (hexa): %lx\n", Retour);
	
	/* point de reprise */
	Retour  = sigsetjmp(contexte,1);
	printf ("retour de setjmp : %ld\n", Retour);
	
	/* essayer des valeurs de i pour obtenir une erreur */
	while (1) {
		printf ("donner Tab_Index : \n");
		Ret_scan = scanf ("%ld",&Tab_Index);
		if (Ret_scan != 1) break;
		printf ("On va faire  Tab[%ld] = 0 (adresse = %p)\n",Tab_Index , &Tab[Tab_Index]);
		Tab[Tab_Index] = 0;
		fflush (stdin);
	}
	exit(0);
}
/**************************************/
/* traitement des signaux             */
/**************************************/
void  Traite_Sig (int Num_Sig ){
	long Retour;
	printf("-- Traite_Sig -- Pid %d recoit signal %d\n", (int)getpid(), Num_Sig);
	printf("-- Traite_Sig -- Erreur sur adresse : %p, Tab_Index = %ld (hexa : %lx)\n", &Tab[Tab_Index], Tab_Index, Tab_Index);
	
	Retour = siglongjmp(contexte, Tab_Index);
	printf ("-- Traite_Sig -- Retour de signal (hexa): %lx\n", Retour);
}

