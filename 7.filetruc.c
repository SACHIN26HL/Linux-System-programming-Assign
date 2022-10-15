#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{

	int fd;



	fd = open("newfile.txt",O_CREAT | O_WRONLY | O_TRUNC, 0777);

	if(fd == -1)
	{

		perror("error in file create\n");
		return 0;
	}


	write(fd, "rtyuihd",7 );
	printf("file created\n");
	close(fd);

	return 0;
}
