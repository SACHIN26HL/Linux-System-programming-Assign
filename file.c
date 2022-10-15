#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
int fd;
fd = open ("newfile.txt",O_CREAT | O_WRONLY  | O_TRUNC);
if (fd == -1)
 /* error */ 
	printf("error");


write(fd, "1234567890", 10);

close(fd);


}
