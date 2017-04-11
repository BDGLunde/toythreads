#include "types.h"
#include "user.h"

void cv_init(struct condvar* cv)
{
	mutex_init(&cv->mtx);
	q_init(&(cv->queue));
	/* fill this in! */
}

void cv_wait(struct condvar* cv, struct mutex* mtx)
{
	/* fill this in! */
	mutex_lock(&cv->mtx);
	q_add(&(cv->queue), getpid());
	if (setpark() < 0) {
		printf(1, "Ay, setpark failed yo\n");
	}

	mutex_unlock(mtx);
	mutex_unlock(&cv->mtx);
	park();
	mutex_lock(mtx);
}

void cv_signal(struct condvar* cv)
{
	/* fill this in! */
	mutex_lock(&cv->mtx);
	if (!((cv->queue).size == 0)) {
		int popped = q_remove(&(cv->queue));
		if (unpark(popped) < 0) {
			printf(1, "failure of unpark\n");
		}
	}
	mutex_unlock(&cv->mtx);
}

void cv_broadcast(struct condvar* cv)
{
	/* fill this in! */
	while (!((cv->queue).size == 0)) {
		int popped = q_remove(&(cv->queue));
		if (unpark(popped) < 0) {
			printf(1, "failure of unpark\n");
		}
	}
}
