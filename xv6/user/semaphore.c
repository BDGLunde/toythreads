#include "types.h"
#include "user.h"
#include "../include/x86.h"

void sem_init(struct semaphore* sem, int initval)
{
	sem->counter = (uint)initval;
	sem->guard = 0;
	q_init(&(sem->queue));
}

void sem_wait(struct semaphore* sem)
{
	while(xchg(&sem->guard, 1) == 1)
		;
	sem->counter --;
//	printf(1, "Value of sem->counter in wait after -- is %d\n", sem->counter);
	if (sem->counter < 0)
	{
		q_add(&(sem->queue), getpid());
//		printf(1, "Just added pid %d to queue, about to park in wait\n", getpid());
		setpark();
		sem->guard = 0;
		park();
	}
	else
		sem->guard =0;
}

void sem_post(struct semaphore* sem)
{
	 while(xchg(&sem->guard, 1) == 1)
                ;

	sem->counter ++;
//	printf(1, "Value of sem->counter in post after ++ is %d\n", sem->counter);
	if (sem->counter <= 0)
	{
//		printf(1, "About to unpark in post\n");
		//int i = 0;
		unpark(q_remove(&(sem->queue)));
		//	printf(1, "ERROR WITH COUNTER MATH\n");
//		printf(1, "About to unpark pid %d\n", i);
		//unpark(i);
	}	
	sem->guard = 0;
}

