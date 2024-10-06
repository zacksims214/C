#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

//error handler, good for debugging
void syserr(char* errm)
{
	write(1, errm, strlen(errm));
	exit(-1);
}

int main(void) {

	//declerations
	pid_t pid;
	char* prompt = "$ ";
	char* message = "Bash Terminal, use CTRL+C to exit\n";

	//write message
	if((write(1, message, strlen(message))) < strlen(message))
        syserr("Write error\n");

	for(;;) 
	{
		//declare buffer for input
		char buffer[256];
		//write prompt to screen and get input
		if(write(1, prompt, strlen(prompt)) < strlen(prompt))
			syserr("Write error\n");

		if(read(0, buffer, sizeof(buffer) - 1) < 0)
			syserr("Read error\n");
		
		//spawn child
		if((pid = fork()) < 0)
			syserr("Fork error\n");

		else if(pid > 0) 
		{
			//parent, wait for child to run command
			if(pid != waitpid(pid, NULL, 0)) 
				syserr("Child exit error\n");
		}
		else 
		{
			//child, execute command	
			if(execl("/bin/sh", "sh", "-c", buffer, (char *) NULL) < 0)
				syserr("Exec error\n");
		}
		//this is required to 'reset' the buffer. mallocing buffer in scope and freeing at end didnt even work for some reason, same block being reused?
		//if a command is longer than the previous one, the null byte gets all messed up and the shell starts not recognzing the remaining chars in buffer
		memset(buffer, '\0', sizeof(buffer));
	}
	exit(0);
}
