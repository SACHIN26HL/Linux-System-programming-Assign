#include<stdio.h>
#include<unistd.h>

int main() {

	int pid;
	int status;

	pid = fork();

	if(pid < 0)
	{
		printf("Error in fork\n");
		return 0;
	}

	if(pid == 0)
	{
		printf("child process\n");
		execl("./helloworld", "./helloworld", (char *)0);
		printf("This wouldn't print\n");
	}
	else
	{
		printf("parent process started\n");
		wait(&status);
		printf("parent process ended\n");
	}
	return 0;
}
