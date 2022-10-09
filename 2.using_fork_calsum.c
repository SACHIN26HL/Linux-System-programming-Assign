#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int array[] = {1, 2, 4, 6, 8, 10, 12, 5};
	int pid;
	int sum1 =0, sum=0;

	int fd[2];
	int first, last;
	int status;

	if(pipe(fd) <= -1)
	{
		printf("eror in pipe\n");
		return 0;
	}
	pid = fork();

	if(pid <= -1)
	{
		printf("Error in fork creation\n");
		return 0;
	}

	if(pid == 0)
	{

		first =0;
		last = (sizeof(array)/sizeof(array[0]))/2;

		for(int i =first; i < last; i++)
		{
			sum1 += array[i];
		}

		printf("Sum of child process : %d\n", sum1);
		close(fd[0]);
		write(fd[1], &sum1, sizeof(sum1));
		close(fd[1]);
		return 1;

	}
	else
	{
		 wait(&status); //wait for child process termination

		 printf("status : %d\n", status);

		first = (sizeof(array)/sizeof(array[0]))/2;
		last = (sizeof(array)/sizeof(array[0]));

		for(int i =first; i < last; i++)
		{
			sum += array[i];
		}
		printf("Sum of parent process : %d\n", sum);
	}

	if(pid != 0)
	{
		close(fd[1]);
		read(fd[0], &sum1, sizeof(sum1));
		close(fd[0]);
		sum += sum1;
	}

	printf("Total sum : %d\n", sum);

	return 0;
}