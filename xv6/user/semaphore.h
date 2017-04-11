
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct semaphore {
	uint counter;
	uint guard;
	queue_t queue;
};

void sem_init(struct semaphore* sem, int initval);
void sem_post(struct semaphore* sem);
void sem_wait(struct semaphore* sem);

#endif
