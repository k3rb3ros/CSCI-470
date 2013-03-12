#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void _fork()
{
		pid_t child = -1;
		unsigned long int pid = 0;
		child = fork();
		pid = child;
		if(child >= 0) // fork was successful
		{
			if(child == 0) // child process
			{	
				_fork();//Call fork recursively
			}
			else // parent process
			{
				while(1) malloc(1024); //waste memory a megabyte at a time
			}
		}
		else // fork failed
		{
			printf("Fork failed\n");
		}

}

int main(int argc, char** argv)
{
		_fork();
		return 0;
}