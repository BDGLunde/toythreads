#include "types.h"
#include "user.h"
#include "../include/x86.h"

void sem_init(struct semaphore* sem, int initval)
{
	sem->counter = initval;
	mutex_init(&sem->mtx);
	q_init(&(sem->queue));
}

void sem_wait(struct semaphore* sem)
{
	mutex_lock(&sem->mtx);
	sem->counter--;
	if (sem->counter < 0)
	{
		q_add(&(sem->queue), getpid());
		setpark();
		mutex_unlock(&sem->mtx);
		park();
	}
	mutex_unlock(&sem->mtx);
}

void sem_post(struct semaphore* sem)
{
	mutex_lock(&sem->mtx);

	(sem->counter)++;
	if (sem->counter <= 0)
	{
		unpark(q_remove(&(sem->queue)));
	}	
	mutex_unlock(&sem->mtx);
}

