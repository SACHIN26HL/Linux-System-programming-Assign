#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sem.h>
#include <semaphore.h>

static int glob = 0;

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;


static void *eventhreadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j;
	
	for (j = 0; j < loops; j++) 
	{
		pthread_mutex_lock(&mtx);

		loc = glob;
		loc++;
		if(loc%2 == 0)
		printf("thread id : %ld  glob : %d is even number\n", pthread_self(), loc);
	
		glob = loc;

		pthread_mutex_unlock(&mtx);
		sleep(1);
	}
	
	printf("glob : %d \n", glob);
	return NULL;
}

static void *oddthreadFunc(void *arg)
{
        int loops = *((int *) arg);
        int loc, j;
        
        for (j = 0; j < loops; j++) 
	{
		pthread_mutex_lock(&mtx);
                loc = glob;
                loc++;

		if(loc%2 != 0)
                printf("thread id : %ld  glob : %d is odd number\n", pthread_self(), loc);
                glob = loc;
		pthread_mutex_unlock(&mtx);
		sleep(1);
        }
        
        printf("glob : %d \n", glob);
        return NULL;
}


int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int loops, s;
	loops = 10; 
	s = pthread_create(&t1, NULL, &eventhreadFunc, &loops);
	if (s != 0)
		perror( "pthread_create");
	
	s = pthread_create(&t2, NULL, &oddthreadFunc, &loops);
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

