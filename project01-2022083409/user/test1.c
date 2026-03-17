#include "kernel/types.h"
#include "user/user.h"
void busywork(int count) {
  volatile int x = 0;
  for (int i = 0; i < count * 100000000; i++) {
    x++;
  }
}
int main(void) {
  int pid = getpid();
  printf("[main] pid: %d\n", pid);
  printf("[main] 현재 큐 레벨: %d\n", getlev());
  printf("[main] MLFQ 모드로 전환\n");
  mlfqmode();
  printf("[main] 계산 작업 시작 (큐 레벨 변화 유도)\n");
  busywork(10);
  printf("[main] 계산 후 큐 레벨: %d\n", getlev());
  printf("[main] setpriority(%d, 0) 호출\n", pid);
  int result = setpriority(pid, 0);
  printf("[main] setpriority 결과: %d\n", result);
  printf("[main] 자식 프로세스 2개 생성\n");
  for (int i = 0; i < 2; i++) {
    int child = fork();
    if (child == 0) {
      if (i == 0) {
        printf("[child-%d] 짧은 작업 시작\n", i);
        busywork(5);
      } else {
        printf("[child-%d] 긴 작업 시작\n", i);
        busywork(15);
      }
      printf("[child-%d] 작업 종료, 큐 레벨: %d\n", i, getlev());
      exit(0);
    }
  }
  wait(0);
  wait(0);
  printf("[main] 모든 자식 종료. FCFS 모드 전환\n");
  fcfsmode();
  printf("[main] 테스트 종료\n");
  exit(0);
}
