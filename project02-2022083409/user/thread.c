#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread.h"

int
thread_create(void (*start_routine)(void *, void *), void *arg1, void *arg2)
{
  void *base = malloc(2 * PGSIZE);
  if(base == 0)
    return -1;

  uint64 addr = (uint64)base;
  void *stack = (void *)((addr % PGSIZE == 0) ? addr : addr + (PGSIZE - addr % PGSIZE));
  int pid = clone(start_routine, arg1, arg2, stack);
  if(pid < 0){
    free(base);
    return -1;
  }

  return pid;
}

int
thread_join()
{
  void *stack;
  int pid = join((void**)&stack);
  if(pid < 0)
    return -1;
  free(stack);
  return pid;
}