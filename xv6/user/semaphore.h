
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct semaphore {
	int counter;
	struct mutex mtx;
	queue_t queue;
};

void sem_init(struct semaphore* sem, int initval);
void sem_post(struct semaphore* sem);
void sem_wait(struct semaphore* sem);

#endif
