#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mtx;
pthread_cond_t  cond;
static int fuel =0;

void *fuelfilling(void *arg)
{
	for(int i = 0; i  <10; i++)
	{
		pthread_mutex_lock(&mtx);
		fuel += 30;
		printf("fuel  filed : %d\n", fuel);
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&cond);
		sleep(1);
	}

	printf("fuel filling completed...\n");

}

void *car(void *arg)
{
	pthread_mutex_lock(&mtx);
	while(fuel < 40)
	{
		pthread_cond_wait(&cond, &mtx);
		printf("car fuel now : %d ......\n", fuel);
	}

		fuel -= 40;
	pthread_mutex_unlock(&mtx);

	printf(" car thread completed...\n");


}

int main()
{
	pthread_t thread_id1, thread_id2;
	int status;

	//initialization
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);


	printf("Thread started............\n");
	status = pthread_create(&thread_id1, NULL, &fuelfilling, NULL);
	if(status !=0 )
	{
		perror("pthread fuelfilling\n");
	        return 0;
	}

	printf("Thread created............\n");
        status = pthread_create(&thread_id2, NULL, &car, NULL);
        if(status !=0 )
        {
                perror("pthread car\n");
                return 0;
        }

	status = pthread_join(thread_id1, NULL);
	if(status != 0)
		perror("pthread_join 1");

	
	status = pthread_join(thread_id2, NULL);
	if(status != 0)
		perror("pthread_join 2");

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);	



	return 0;
}

