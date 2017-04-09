#include "types.h"
#include "user.h"
#include "../include/x86.h"

void spin_init(struct spinlock* lk)
{
	/* fill this in! */
	lk->locked = 0;
	lk->created = 1;
}

void spin_lock(struct spinlock *lk)
{
	while(xchg(&lk->locked, 1) != 0)
		;
}

void spin_unlock(struct spinlock *lk)
{
	xchg(&lk->locked, 0);
}

