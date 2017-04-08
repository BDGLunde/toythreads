
#include "types.h"
#include "user.h"

int thread_create(void (*thfunc)(void*), void* arg)
{
	void *thstack;
	if ((thstack = malloc(PGSIZE)) == 0)
		return -1;
	
	return clone(thfunc, arg, thstack);
}

int thread_join(void)
{
	int exitpid;
	void *thstack;
	if ((exitpid = join(thstack)) == -1)
		return -1;
	free(thstack);
	return exitpid;
}
