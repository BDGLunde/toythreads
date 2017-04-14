#include "types.h"
#include "user.h"

void cv_init(struct condvar* cv)
{
	mutex_init(&cv->mtx);
	q_init(&(cv->queue));
}

void cv_wait(struct condvar* cv, struct mutex* mtx)
{
	mutex_lock(&cv->mtx);
	q_add(&(cv->queue), getpid());
	setpark();
	mutex_unlock(mtx);
	mutex_unlock(&cv->mtx);
	park();
	mutex_lock(mtx);
}

void cv_signal(struct condvar* cv)
{
	mutex_lock(&cv->mtx);
	if (!((cv->queue).size == 0)) {
		int popped = q_remove(&(cv->queue));
		unpark(popped);
	}
	mutex_unlock(&cv->mtx);
}

/* Like signal, but wakes up all waiters */
void cv_broadcast(struct condvar* cv)
{
	mutex_lock(&cv->mtx);
	while (!((cv->queue).size == 0)) {
		int popped = q_remove(&(cv->queue));
		unpark(popped);
	}
	mutex_unlock(&cv->mtx);
}
