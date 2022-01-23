#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define MAX_COUNT 12
#define COUNT_TRIGGER 10
#define NUM_THREADS 3

//Global Variable to keep track of the count
int count = 0;

pthread_mutex_t mtx;
pthread_cond_t count_conditionVar;


//Struct to store Thread details
struct threadInfo {
	int threadID;
	int threadData;
};

void *addCount(void *args)
{
    struct threadInfo *ptr = (struct threadInfo*)args;

    for(int i = 0; i < COUNT_TRIGGER; i++)
    {
        pthread_mutex_lock(&mtx);
        count++;
        cout << "Thread ID: " << ptr->threadID << endl;
        cout << "Count Value: " << count << endl;
        if(count == MAX_COUNT)
        {
            pthread_cond_signal(&count_conditionVar);
            //cout << "Condition Variable Singal True" << endl;
        }

        pthread_mutex_unlock(&mtx);
        sleep(1);

    }

    pthread_exit(0);
}


void *checkCount(void *args)
{
    struct threadInfo *ptr = (struct threadInfo*)args;

    pthread_mutex_lock(&mtx);
    cout << "Thread ID Check Count Func: " << ptr->threadID << endl;
    cout << "Count Value Check Count Func: " << count << endl;
    if(count < MAX_COUNT)
    {
        pthread_cond_wait(&count_conditionVar , &mtx);
        cout << "Condition Variable Signaled" << endl;
    }

    pthread_mutex_unlock(&mtx);

    pthread_exit(0);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    struct threadInfo threadDetails[NUM_THREADS];

    pthread_mutex_init(&mtx , 0);
    pthread_cond_init(&count_conditionVar , 0);

    for(int i = 0; i < NUM_THREADS; i++)
	{
		threadDetails[i].threadID = i;
		threadDetails[i].threadData = i*i;
    }

    pthread_create(&threads[0] , NULL, checkCount , (void*)&threadDetails[0]);
    pthread_create(&threads[1] , NULL, addCount , (void*)&threadDetails[1]);
    pthread_create(&threads[2] , NULL, addCount , (void*)&threadDetails[2]);


    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i] , 0);

    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&count_conditionVar);

    return 0;

}