#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void allChildren(int numProcs) {
	
	pid_t pid;

	for(int x = 0; x < numProcs; x++) {
		pid = fork();

		if(pid < 0) {
			printf("ERROR: bad fork\n");
			exit(0);
		}
		else if(pid == 0) {
			//child
			printf("Hello from child, PID: %d\n", getpid());
			exit(0);
		}
		else {
			//parent
			waitpid(pid, NULL, 0);
		}

	}

}

int main(int argc, char** argv) {

	//get command line arg for # of children
	if(argc < 2) {
		printf("No argument specified, run again with args\n");
		exit(0);
	}
	
	int numProcs = atoi(argv[1]);
	
	allChildren(numProcs);
	
	return 0;
}
