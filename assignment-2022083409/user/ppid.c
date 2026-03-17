#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
  printf("My studnet ID is 2022083409\n");
  printf("My pid is %d\n", getpid());
  printf("My ppid is %d\n", getppid());
  exit(0);
};