// prioritytest.c - forks 4 CPU-bound children, each sets its own priority
// with nice(), runs a long nested loop, reports how long it took, and exits.
// Higher priority => longer time quantum => should finish earlier.

#include "types.h"
#include "stat.h"
#include "user.h"

#define NCHILD 4
#define OUTER  5000
#define INNER  10000

void
worker(int priority)
{
  int i, j;
  volatile uint x = 0;//volatile so the compiler cannot drop the loops
  int start, end;

  if(nice(priority) < 0){
    printf(1, "pid %d: nice(%d) failed\n", getpid(), priority);
    exit();
  }

  start = uptime();
  for(i = 0; i < OUTER; i++){
    for(j = 0; j < INNER; j++){
      x += i + j;
    }
  }
  end = uptime();

  printf(1, "pid %d priority %d: started at tick %d, finished at tick %d (took %d)\n",
         getpid(), priority, start, end, end - start);
  exit();
}

int
main(void)
{
  int prio[NCHILD] = {3, 4, 8, 7};
  int i, pid;

  printf(1, "prioritytest: starting %d processes\n", NCHILD);

  for(i = 0; i < NCHILD; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "prioritytest: fork failed\n");
      exit();
    }
    if(pid == 0)
      worker(prio[i]);
  }

  for(i = 0; i < NCHILD; i++)
    wait();

  printf(1, "prioritytest: all processes finished\n");
  exit();
}
