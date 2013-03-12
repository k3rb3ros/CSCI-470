#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argv, char** argc)
{
	pid_t child = -1;
	child = fork();
	int status = 0;

	if (child < 0) // fork failed
	{
		printf("Fork failed, quitting!!!!!!\n");
	    return 1;
	}
	
	if (child == 0) {
		execv("exec/exec_me",NULL);
	} else {		
		waitpid(child, &status , 0);
		printf("pid(%d): %d",child, status);
	}
	//if(execl("/home/k3rb3ros/csci470/CSCI-470/fork_fun/exec_me", NULL) != -1) return 0;
	//return 1;
}