#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<wait.h>

int main()
{
    pid_t id;
    id=fork();
    if(id==0)
    {
	int i;
        while(1)
	{
            for(i=0;i<500;i++)
	    {
                printf("%d ",i);
	    }
	    printf("\n");
	    //sleep(1);
	}
    }
    else
    {
	sleep(5);
	kill(id,SIGKILL);
	wait(NULL);
    }
    return 0;
 }
	    

