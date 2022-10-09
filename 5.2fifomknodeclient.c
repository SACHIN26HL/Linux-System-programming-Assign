#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define FILE_NAME "fifo_file"
int main()
{
	int fd;
	char buffer[100];

	fd = open(FILE_NAME, O_CREAT | O_WRONLY);

	if(fd == -1)
	{
		perror(" Error in create a file\n");
		printf("File create error\n");
		return 0;
	}

	while(1)
	{
		printf("Enter a string : ");
		scanf("%s", buffer);

		if(strcmp(buffer, "end") == 0)
		{
			printf("......Completed......\n");
			break;
		}else
		{
			write(fd, buffer, strlen(buffer)+1);
		}

	}
	close(fd);
	return 0;

}