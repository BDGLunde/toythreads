"Master" merge branch for part 1:

The first step in this project is to add a system call by which a process can create a new thread:

int clone(void (*fn)(void*), void* arg, void* ustack);
clone() should return the pid of the newly-created thread to the parent, start the new thread with a call to the function fn, passing the provided argument arg. The  ustack argument specifies the base address of the region of memory to be used as the new thread's stack (it should be one page in size, like the stack created by the  exec() syscall). Recall that the stack grows down, however, so the new thread's stack pointer should start at the opposite end of this region. The calling process must allocate space for the new thread's stack before calling clone(). On failure, clone should simply return -1 to the original thread.

The new thread should share the virtual address space of the parent thread. As in  fork(), file descriptors should also be copied into the new thread. As in exec(), the new thread's stack should be initialized with a fake return address of 0xffffffff so that if the new thread returns from its outermost function it triggers a trap. To avoid this, a thread should call exit() (like a regular process does) when it has nothing left to do. (The arg argument to fn will of course also need to be place on its initial stack.)

After implementing clone(), you should then create a corresponding system call that is to clone() what wait() is to fork():

int join(void** ustack);
Like wait(), join() returns the PID of the child thread that has exited (or -1 if the process has no child threads). When a thread exits, the base address of its stack (the address that was passed as the ustack argument to the clone() call that created it) should be passed back to the calling process via the ustack argument to the join() (note that this is a void**, not a void*). join() should not act on other processes, only threads (i.e. processes that share the same virtual address space as the calling process). Similarly, you should modify wait() so that it operates only on other processes in different virtual address spaces, not other threads in the same one.
