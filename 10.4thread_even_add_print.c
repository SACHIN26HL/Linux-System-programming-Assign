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
sem_t even;
sem_t odd;
//static void *threadFunc(void *arg)
/*{
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
}*/


void *eventhreadFunc(void)
{
        while(1)
	{
		semget(&even);
		printf("%d ",glob++);
		sempost(&odd);
	}
}

void *oddthreadFunc(void)
{
        while(1)
        {
                semget(&odd);
                printf("%d ",glob++);
                sempost(&even);
        }
}
int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int loops, s;
	loops = 10; 
	sem_init(&even,0,0);
	sem_init(&odd,0,1);
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
