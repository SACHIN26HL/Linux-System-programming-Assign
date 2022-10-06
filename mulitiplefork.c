#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	int id, id1;

	id = fork();
	id1 = fork();


	if(id == 0)
	{
		printf("1\t");
		if(id1 == 0)
		{
			printf("3\n");
		}
		else
		{
			printf("5\n");
		}
	}
	else
	{
		printf("2\t");
		if(id1 == 0)
		{
		printf("4\n");
		}
		else
		{
			printf("6\n");
		}

	}


	return 0;
}