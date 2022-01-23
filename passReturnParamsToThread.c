#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void *func1(void *param1)
{
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 10;

	for(int i = 0; i < 8;i++)
	{
        sleep(1);
		printf("Func 1\n");
        (*ptr)++;
	}

    //printf("Entered Here\n");
	return (void*)ptr;

    //return NULL;

}

void *func2(void *param1)
{
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 10;

	for(int i = 0; i < 8;i++)
	{
        sleep(1);
		printf("Func 2\n");
        (*ptr)++;
	}

    //printf("Entered Here\n");
	return (void*)ptr;

    //return NULL;

}




int main()
{
    int *result1;
    int *result2;
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1 , NULL, func1, NULL);
	pthread_create(&t2 , NULL, func2, NULL);
    //func2();


	pthread_join(t1 , (void*)&result1);
    pthread_join(t2 , (void*)&result2);


    printf("Result from Thread 1 = %d\n", *result1);
    printf("Result from Thread 2 = %d\n", *result2);


    printf("Entered Main\n");

	return 0;
}