#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv)
{
	int arr[2] = {-1, -1};
	int status = 0;
	char data[16] = "=^_^=\0";
	
	pid_t child = -1;
	
	pipe(arr);
	
	child = fork();

	
	if (child < 0) //failed to fork
	{
		cerr << "Unable to fork\n";
		exit(1);
	}
	if(child == 0) //child process
	{			
		read(arr[0], &data, 16); //Read the data buffer from the pipe
		cout << data << endl;
		exit(0);
	}
	else //parent
	{
		char* _data = "Ryan is awesome\0";
		write(arr[1], _data, 16);
	}
	return 0;
}
