#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#define FILE_NAME "fifo_file_twoway"
int main()
{
	int fd;
	char buffer[1000];
	char read_buffer[1000];

	
	fd = open(FILE_NAME, O_CREAT | O_RDWR);

	if(fd == -1)
	{
		perror("Error in File\n");
		return 0;
	}

	while(1)
	{
		printf("\nRead message : ");
		read(fd, read_buffer, 1000);
		printf("%s", read_buffer);

		printf("\nEnter a msg : ");
		scanf("%s", buffer);
		write(fd, buffer, strlen(buffer)+1);

		
		if(strcmp(buffer, "end") == 0)
		{
			printf("...completed...\n");
			break;
		}
	}

	close(fd);
	return 0;
}