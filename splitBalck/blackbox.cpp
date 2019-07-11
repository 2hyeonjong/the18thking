#include "header.h"
#include "thread1.cpp"
#include "thread2.cpp"

void* firstThreadRun(void *);
void* secondThreadRun(void *);



int main()
{
	pthread_t firstThread, secondThread;
	int threadErr;


	if(threadErr = pthread_create(&firstThread, NULL, firstThreadRun, NULL))
	{
		printf("Thread Err = %d", threadErr);
	}


	if(threadErr = pthread_create(&secondThread, NULL, secondThreadRun, NULL))
	{
		printf("Thread Err = %d", threadErr);
	}
	while(1);
}

