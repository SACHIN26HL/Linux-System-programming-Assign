#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

#include <pthread.h>



static int glob = 0;
static void *
/* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j;
	for (j = 0; j < loops; j++) {
		loc = glob;
		loc++;
		printf("thread id : %ld  glob : %d \n", pthread_self(), loc);
		glob = loc;
	}
	printf("glob : %d \n", glob);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int loops, s;
	loops = 10; 
	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0)
		perror( "pthread_create");
	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0)
		perror("pthread_create");
	s = pthread_join(t1, NULL);
	if (s != 0)
		perror("pthread_join");

	printf("..........\n");
	s = pthread_join(t2, NULL);
	if (s != 0)
		perror("pthread_join");
	printf("glob = %d\n", glob);
	exit(0);
}
