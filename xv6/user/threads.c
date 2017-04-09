#include "types.h"
#include "user.h"


int thread_create(void (*thfunc)(void*), void* arg)
{
	void *thstack;
	if ((thstack = malloc(4096)) == 0)
		return -1;
	return clone(thfunc, arg, thstack);
}

int thread_join(void)
{
	int exitpid;
	int n = 10; // Don't overwrite code segment, lol
	void **thstack = (void *)&n;
	if ((exitpid = join(thstack)) == -1)
		return -1;
	free(*thstack);
	return exitpid;
}
