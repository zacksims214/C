#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

//Recursive function to handle the chain
void chain(int numProcs, int x) {
    pid_t pid = fork();
    
    //test return values
    if(pid < 0) {
        printf("ERROR: bad fork\n");
		exit(0);
    }
    else if(pid > 0) {
        //parent, just waits for child to exit 
        waitpid(pid, NULL, 0);
    }
    else {
        //child
        //base case ish, youngest child exits, its parent isnt waiting anymore so it exits, etc until done 
        if(x == numProcs-1) {
            printf("End of the chain, hello from PID: %d\n", getpid());

            //system("ps");     //can turn on for "proof of concept". Once end msg prints, we can ps to see we have the original parent, and then all the children created
            exit(0);
        }
        else {
            //call again to fork another process, update counter
            chain(numProcs, x+1);
            exit(0);
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
    chain(numProcs, 0);
	
	return 0;
}