
#ifndef SPINLOCK_H
#define SPINLOCK_H

struct spinlock {
	/* fill this in! */	
	uint locked;		// Is the lock held?
	int created;
};

void spin_init(struct spinlock* lk);
void spin_lock(struct spinlock *lk);
void spin_unlock(struct spinlock *lk);

#endif
