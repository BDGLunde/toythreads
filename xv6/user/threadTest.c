#include "types.h"
#include "stat.h"
#include "user.h"
#include "threads.h"

void test(void *arg)
{
	int x = 5;
	printf(1, "x at %p\n", &x);
	printf(1, "thread with pid: %d\n", getpid());
	exit();
}

int main() 
{
	int x = 10;
	printf(1, "Main x at %p\n", &x);
	int pid = thread_create(test, (void*)x);
	int pid2 = thread_create(test, (void*)x);
	thread_join();
	thread_join();
	printf(1, "Thread1 exited w/ pid %d\n", pid);
	printf(1, "Thread2 exited w/ pid %d\n", pid2);

	exit();
}


