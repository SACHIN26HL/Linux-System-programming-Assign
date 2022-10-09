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

 mknod(FILE_NAME, S_IFIFO|0640, 0);
	fd = open(FILE_NAME, O_RDONLY);

	if(fd == -1)
	{
		perror(" Error in open a file\n");
		printf("File open error\n");
		return 0;
	}

	while(1)
	{
		
		read(fd, buffer, 100);

		if(strcmp(buffer, "end") == 0)
		{
			printf("...read file completed....\n");
			break;
		}
		printf(" Receive string : %s \n", buffer);
		

	}
	close(fd);
	return 0;

}