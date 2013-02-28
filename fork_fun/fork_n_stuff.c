#include <stdio.h>
#include <unistd.h>

int main(int argv, char** argc)
{
	if(execl("/home/k3rb3ros/csci470/CSCI-470/fork_fun/exec_me", NULL) != -1) return 0;
	return 1;
}