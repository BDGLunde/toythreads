#include "types.h"
#include "user.h"
#include "../include/x86.h"

void mutex_init(struct mutex* mtx)
{
	mtx->flag = 0;
	mtx->guard = 0;
	//mtx->heldBy = 0;
	q_init(&(mtx->queue));
}

void mutex_lock(struct mutex* mtx)
{
	while(xchg(&mtx->guard, 1) == 1)
		;
	if (mtx->flag == 0) 
	{
		mtx->flag = 1;
		//mtx->heldBy = getpid();
		mtx->guard = 0;
	} else {
		q_add(&(mtx->queue), getpid());
		setpark();
		mtx->guard = 0;
		//printf(1, "Lock held by pid: %d\n", mtx->heldBy);
		park();
	}
}

void mutex_unlock(struct mutex* mtx)
{
	while(xchg(&mtx->guard, 1) == 1)
		;
	
	int val;
	
	//If q empty
	if ((val = q_remove(&(mtx->queue))) == -1)
		mtx->flag = 0;
	else
	{
		unpark(val);
//		mtx->flag = 0;
	}
	mtx->guard = 0;
}
