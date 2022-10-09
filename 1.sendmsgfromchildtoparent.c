#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd[2];
	//fd[0] = read
	//fd[1] = write
	char buf[100];
	char buf1[100];
	int pid;

	if(pipe(fd) == -1)
	{
		printf("Error in pipe\n");
		return 0;
	}
	printf("......Start......\n");
	pid = fork();

	if(pid <= -1)
	{
		printf("Error in fork\n");
		return 0;
	}

	if(pid == 0)
	{
		
		close(fd[1]);
		printf("msg from parent : ");
		read(fd[0], buf1, sizeof(buf1));
		printf("%s",buf1);
		close(fd[0]);
	

	}
	else
	{
		
		close(fd[0]);
		printf("Enter a message : ");
		scanf("%s", buf);
		write(fd[1], buf, strlen(buf)+1);
		printf("parent message :%s\n",buf);
		close(fd[1]);

	
	}

	return 0;

}
