#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

#include <pthread.h>



static int glob = 0;
static void *cap_threadFunc(void *arg)
{
	char *str = ((char *) arg);
	int loc, j;
	printf("capital String : ");
	for (j = 0; j < strlen(str) +1; j++)
       	{
		if(str[j] >= 97 && str[j] <= 122)
			printf("%c", str[j]-32);
		else if(str[j] >= 65 && str[j] <= 90)
			printf("%c", str[j]);

	}
	printf("\n");
	return NULL;
}
static void *small_threadFunc(void *arg)
{
        char * str = ((char *) arg);
        int loc, j;
        printf("small string : ");
        for (j = 0; j < strlen(str) +1; j++)
        {
                if(str[j] >= 97 && str[j] <= 122)
                        printf("%c", str[j]);
                else if(str[j] >= 65 && str[j] <= 90)
                        printf("%c", str[j]+32);

        }

        printf("\n");
        return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int  s;
 
	char *string =  "aBcDefghtuDFGHJKWERTYU";
	s = pthread_create(&t1, NULL, cap_threadFunc, string);
	if (s != 0)
		perror( "pthread_create");
	
	string ="qwrrDFGYUfgjaaaaaaBBBBBBB";
	s = pthread_create(&t2, NULL, small_threadFunc, string);
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
