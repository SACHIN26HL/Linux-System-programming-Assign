#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <error.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
	long mtype;// msgtype  > 0
	char data[20];

};
int main(int argc, char *argv[])
{
	int id;
	struct msgbuf v;

	id = msgget(3, IPC_CREAT | 0666);
	if(id == -1)
	{
		perror("msgget");
		return 0;
	}
	
	printf("Before receiving the message ...\n");

	msgrcv(id, &v, 20, 2,0);

	printf("data : %s \n", v.data);

   return 0;
}
