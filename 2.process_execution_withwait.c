#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{


	int id;
	int n;

	id = fork();

	if(id != 0)
	{
		printf("parent id : %d\n", getppid());
		n=6;
		wait();
	}else if(id == 0)
	{
		printf("child process id : %d \n", getpid());
		n =1;
		//wait();
	}

	for(int i = n; i < 5+n; i++)
	{
		printf("%d\t", i);
	}

	if(id != 0)
	printf("\n");

	return 0;
}