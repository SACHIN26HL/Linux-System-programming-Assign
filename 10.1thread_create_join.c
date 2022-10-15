#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>


int sub_thread_fun(char *msg);

int main()
{
	pthread_t pid;
	int status;
       	void* retvalue;

	printf(",,,,,,,,main function start.......\n");

	status = pthread_create(&pid, NULL, sub_thread_fun, "Hello thread");

	if(status != 0)
	{
		perror("pthread create error\n");
		return 0;
	}

	printf("thread created \n");

	sleep(2);
	status = pthread_join(pid, &retvalue);
	if(status != 0)
	{
		perror("pthread join error\n");

	}

	printf("thread terminated and return value : %ld\n",(long) retvalue);

	return 0;
}


int sub_thread_fun(char *msg)
{
	printf("start thread....\n");
//	pthread_detach(pthread_self());
	printf("messgae from main : %s \n", msg);


	return strlen(msg);
}

