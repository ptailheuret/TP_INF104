#include <stdio.h>
#include <semaphore.h>

#include "semaph.h"

/* Fermeture de semaphores deja existants */

int main(int argc, char *argv[]){
	sem_t *mutex;
	
	mutex = sem_open(VERROU,0,0644,0);
	if(mutex == SEM_FAILED){
		perror("pb open VERROU");
 	}
	sem_close(mutex);
	sem_unlink(VERROU);
	
	mutex = sem_open(VERROULEC,0,0644,0);
	if(mutex == SEM_FAILED){
		perror("pb open VERROULEC");
 	}
	sem_close(mutex);
	sem_unlink(VERROULEC);
	
	mutex = sem_open(COUPEFILE,0,0644,0);
	if(mutex == SEM_FAILED){
		perror("pb open COUPEFILE");
 	}
	sem_close(mutex);
	sem_unlink(COUPEFILE);

	printf("reset : fin \n");
	return 0;
}
