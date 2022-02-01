#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>



#define THREAD_NUM 6

sem_t semaphore;

void *routine(void *args)
{
    sem_wait(&semaphore);
    sleep(1);
    printf("Hello from thread number = %d\n", *(int*)args);
    sem_post(&semaphore);

    free(args);
}


int main()
{
    pthread_t threads[THREAD_NUM];

    /*Depending on the initialization of the semaphore, multiple threads can acquire the semaphore and start executing*/
    /*If the semaphore count is 0 , the thread will have to wait until other threads release the semaphore*/
    sem_init(&semaphore , 1 , 3);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        pthread_create(&threads[i] , NULL , &routine , a);

    }

    for (size_t i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threads[i] , NULL);
    }

    return 0;
    
}