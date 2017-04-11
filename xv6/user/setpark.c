#include "types.h"
#include "stat.h"
#include "user.h"

//struct spinlock *lk;
int status = 0;
struct spinlock lk;

void f(void *arg)
{
  // spin_init(&lk);
  //spin_lock(&lk);
  //status = *((int*)arg);
 
  if(setpark() < 0)
          printf(1, "setpark failed!\n");
  printf(1, "thread has setparked\n");

  sleep(200);

  park();
  printf(1, "park returned fast\n");

  int i;

  for(i = 0; i < 10; i++)
  {
      int tmp = status;
      sleep(1);
      status = tmp +1;
  }

  if(unpark(getpid()) < 0)
          printf(1, "in thread, unpark failed! pid %d\n", getpid() + 1);

  exit();
}



int main()
{
  if(thread_create(&f,(void*)1) < 0)
           printf(2, "clone failed");

  printf(1, "sleeping\n");
  sleep(30);
  printf(1, "awake\n");

  if(unpark(getpid()+1) < 0)
      printf(1, "unpark failed to find a parked thread!\n");
  else
	printf(1, "main succesfully unparked a setparked trhead\n");

//  sleep(1000);
//  if(unpark(getpid()+1 < 0)
//	printf(1, "unpark failed in main after sleeping a while\n");
//  else
//	printf(1, "unpark returned succesfully in main\n");

  thread_join();

  //thread_create(&f,arg);
  //thread_join();
  //thread_create(&f,arg);
  //thread_join();

  printf(1, "status = %d\n", status);
 exit();
}
