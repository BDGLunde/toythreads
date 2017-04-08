
#ifndef SPINLOCK_H
#define SPINLOCK_H

struct spinlock {
	/* fill this in! */	
	uint locked;		// Is the lock held?

	// For debugging:
	char *name;		// Name of lock.
	struct cpu *cpu;	// The cpu holding the lock.
	uint pcs[10];		// The call stack (an array of prog counters)
};

void spin_init(struct spinlock* lk);
void spin_lock(struct spinlock *lk);
void spin_unlock(struct spinlock *lk);

#endif
