#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

pthread_t mainThread;
pthread_attr_t mainThreadAttributes;
int rt_max_prio, rt_min_prio, min;
struct sched_param main_param;

void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
     case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
     case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n");
       break;
     case SCHED_RR:
           printf("Pthread Policy is SCHED_RR\n");
           break;
     default:
       printf("Pthread Policy is UNKNOWN\n");
   }
}

void *function1(void *param1)
{
    while (1)
    {
        /* code */
        print_scheduler();
        sleep(3);
    }

    return NULL;
    
}

int main()
{
   int rc, scope;

   printf("Before adjustments to scheduling policy:\n");
   print_scheduler();

   pthread_attr_init(&mainThreadAttributes);
   pthread_attr_setinheritsched(&mainThreadAttributes, PTHREAD_EXPLICIT_SCHED);
   pthread_attr_setschedpolicy(&mainThreadAttributes, SCHED_FIFO);

   rt_max_prio = sched_get_priority_max(SCHED_FIFO);
   rt_min_prio = sched_get_priority_min(SCHED_FIFO);

   main_param.sched_priority = rt_max_prio;
   rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);


//    if (rc)
//    {
//        printf("ERROR; sched_setscheduler rc is %d\n", rc);
//        perror("sched_setschduler"); exit(-1);
//    }

   printf("After adjustments to scheduling policy:\n");
   print_scheduler();

   main_param.sched_priority = rt_max_prio;
   pthread_attr_setschedparam(&mainThreadAttributes, &main_param);

   rc = pthread_create(&mainThread, &mainThreadAttributes, function1, (void *)0);

//    if (rc)
//    {
//        printf("ERROR; pthread_create() rc is %d\n", rc);
//        perror("pthread_create");
//        exit(-1);
//    }

   pthread_join(mainThread, NULL);

    return 0;
}