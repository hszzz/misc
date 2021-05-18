#include "threadpool.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void task_func(void* arg) {
	int n = *(int*)arg;
	int t = rand() % 1;
	sleep(t);
	printf("thread id = %ld, number = %d, sleep time = %d\n", pthread_self(), n, t);
}

int main() {
	threadpool* pool = threadpool_create(3, 10, 10);

	int i = 0;
	for (i; i<100; i++) {
		int* num = (int*)malloc(sizeof(int));
		*num = i;
		threadpool_add(pool, task_func, (void*)num);
	}
	printf("all tasks push into queue ...\n");
	
	sleep(10);
	int e = threadpool_destroy(pool);
    return 0;
}
