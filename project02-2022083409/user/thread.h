#ifndef THREAD_H
#define THREAD_H

#define PGSIZE 4096 // bytes per page

int thread_create(void (*start_routine)(void *, void *), void *arg1, void *arg2);
int thread_join();

#endif