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
	(sem->counter)--;
	if (sem->counter < 0)
	{
		q_add(&(sem->queue), getpid());
		setpark();
		sem->guard = 0;
		park();
	}
	else {
		//sem->counter++;
		xchg(&sem->guard, 0);
	}
}

void sem_post(struct semaphore* sem)
{
	while(xchg(&sem->guard, 1) == 1)
                ;

	(sem->counter)++;
	if (sem->counter < 0)
	{
		unpark(q_remove(&(sem->queue)));
	}	
	xchg(&sem->guard, 0);
}

