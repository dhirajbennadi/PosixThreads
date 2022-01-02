#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 10

//Global pthread implementation of mutex lock
pthread_mutex_t mtx;

//Struct to store Thread details
struct threadInfo {
	int threadID;
	int threadData;
};

void *printThreadDetails(void * args){
	struct threadInfo *ptr = (struct threadInfo*)args;

	//Get the lock before entering the critical section
	pthread_mutex_lock(&mtx);
	cout << "Printng from thread number : " << ptr->threadID << endl;
	cout << "Value of Thread Data : " << ptr->threadData << endl;

	//Release the lock on exiting critical section
	pthread_mutex_unlock(&mtx);

	pthread_exit(NULL);
}


int main()
{
	pthread_t threads[NUM_THREADS];
	struct threadInfo threadDetails[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++)
	{
		threadDetails[i].threadID = i;
		threadDetails[i].threadData = i*i;

		pthread_create(&threads[i] , NULL, printThreadDetails, (void*)&threadDetails[i]);
	}


	void *ret;

	for(int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i] , &ret);
	}


	pthread_exit(NULL);

	return 0;
}
