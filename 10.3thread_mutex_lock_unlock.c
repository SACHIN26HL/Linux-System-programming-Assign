#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

#include <pthread.h>



static int glob = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  //statically
static int *threadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j;
	int status ;

	status = pthread_mutex_lock(&mtx);

	if(status != 0)
		perror("pthread mutex lock");


	for (j = 0; j < loops; j++) 
	{

		loc = glob;
		loc++;
		printf("thread id : %ld  glob : %d \n", pthread_self(), loc);
		glob = loc;
	}
	status = pthread_mutex_unlock(&mtx);
	
	if(status != 0)
		perror("pthread mutex lock");
	
	printf("glob : %d \n", glob);
	return glob;
}

int main(int argc, char *argv[])
{


	pthread_t t1, t2;
	int thread_ret;
	int loops, s;
	loops = 10; 


	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0)
		perror( "pthread_create");

	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0)
		perror("pthread_create");

	s = pthread_join(t1, &thread_ret);
	printf("t1 return value : %d\n", thread_ret);
	if (s != 0)
		perror("pthread_join");

	printf("..........\n");

	s = pthread_join(t2, &thread_ret);
	printf("t2 return value : %d\n", thread_ret);
	if (s != 0)
		perror("pthread_join");
	printf("glob = %d\n", glob);
	exit(0);
}
