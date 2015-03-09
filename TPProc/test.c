#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void)
{
	pid_t pids[20];
	int i;
 
	for (i = 19; i >= 0; --i) {
		pids[i] = fork();
		if (pids[i] == 0) {
			sleep(2*i+1);
			_exit(0);
		}
	}
 
	for (i = 19; i >= 0; --i)
		waitpid(pids[i], NULL, 0);
 
	return 0;
}
