
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct semaphore {
	int counter; // CANNOT be uint, since counter may be negative
	struct mutex mtx;
	queue_t queue;
};

void sem_init(struct semaphore* sem, int initval);
void sem_post(struct semaphore* sem);
void sem_wait(struct semaphore* sem);

#endif
