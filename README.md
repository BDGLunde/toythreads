The purpose of this project is to experiment with implementing threading capabilities for xv6.

I'm not sure if this can be considered "true" threading, as our "threads" are currently treated more specifically as separate processes (with their own pids) which share the same address space (by way of receiving the same page table) as their parent. Perhaps this still holds true in "real" operating systems, though perhaps under a few more layers of abstraction that hides this.
