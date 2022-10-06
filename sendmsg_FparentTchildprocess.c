#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>




int main()
{
	int id;

	char msg[100];

	id = fork();

	if(id == 0)
	{
		printf("I'm child process\n");
		printf("Child process id : %d\n\n", getpid());



	}
	else if(id > 0)
	{
		printf("I'm parent process\n");
		printf("parent process id : %d\n" , getppid());
		printf("\n";)


	}
	else
	{
		printf("Error\n");
	}



	return 0;
}