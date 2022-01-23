#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *func1(void *param1)
{
	while(1)
	{
		printf("Func 1\n");
		sleep(1);
	}

	return NULL;

}

void *func2(void *param1)
{
	while(1)
	{
		printf("Func 2\n");
		sleep(2);
	}

	return NULL;

}


int main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1 , NULL, func1, NULL);
	pthread_create(&t2 , NULL, func2, NULL);

	pthread_join(t1 , NULL);
	pthread_join(t2 , NULL);


	return 0;
}
