#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int i, le_nombre, ret;
	char * message []= {"...", "est premier"};
	char * reponse;
	int fonc(int n);
	
	if (argc != 2) {
		printf("Utilisation : %s <nbre a tester>\n", argv[0]);
		return 1;
	}
	
	le_nombre = atoi(argv[1]);
	
	for (i=1; i<=le_nombre; i++) {
		ret = fonc(i);
		reponse = message[ret];
		printf("main : %d  %s\n", i, reponse);
	}
	
	return 0;
}

/************ fonc ************/
int fonc(int n){
	int i, premier = 1;
	for (i=2; i*i<=n; i++) {
		if (n%i == 0){
			premier = 0;
		    break;
		}
	}
	return premier;
}	
