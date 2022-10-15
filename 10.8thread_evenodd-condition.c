#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mtx;
pthread_cond_t  cond;
static int number =0;

void *number_inc(void *arg)
{
	int count = *(int *)arg;
	for(int i = 0; i  < count; i++)
	{
		pthread_mutex_lock(&mtx);
		number++;
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&cond);
		sleep(1);
	}

	printf(" completed. t1..\n");

}

void *condition_check(void *arg)
{
	int count = *(int *)arg;
	pthread_mutex_lock(&mtx);
	while(number < count)
	{
		pthread_cond_wait(&cond, &mtx);
		if(number%2)
			printf("%d : is odd number\n", number);
		else
			printf("%d : is even number\n",number);
	}

	pthread_mutex_unlock(&mtx);

	printf(" thread  t2 completed...\n");


}

int main()
{
	pthread_t thread_id1, thread_id2;
	int status, num_range;

	//initialization
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);

	printf("Entrer a range : ");
	scanf("%d", &num_range);


	printf("Thread started............\n");
	status = pthread_create(&thread_id1, NULL, &number_inc, &num_range);
	if(status !=0 )
	{
		perror("pthread fuelfilling\n");
	        return 0;
	}

	printf("Thread created............\n");
        status = pthread_create(&thread_id2, NULL, &condition_check, &num_range);
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

	printf("main terminated..\n");

	return 0;
}

