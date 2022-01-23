#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#define MAX_VAL 100000000UL
uint32_t counter = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *increment(void* param)
{
    for(int i = 0; i < MAX_VAL; i++)
    {
        pthread_mutex_lock(&m);
        counter++;
        pthread_mutex_unlock(&m);
    }

    return NULL;
}

int main()
{
    pthread_t t1;
    pthread_t t2;

    struct timespec before;
    struct timespec  after;
    clock_gettime(CLOCK_REALTIME , &before);
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter Value = %d", counter);
    clock_gettime(CLOCK_REALTIME , &after);

    printf("Time Value in seconds = %ld\n", after.tv_sec - before.tv_sec);
    printf("Time Value in nano seconds =%ld\n", after.tv_nsec - before.tv_nsec);

    return 0;
}
