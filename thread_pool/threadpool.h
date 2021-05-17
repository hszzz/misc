#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>

typedef struct task {
	void (*callback)(void* arg);
	void* arg;
} task;

typedef struct threadpool {
	task* tasks;
	int queue_capacity;
	int queue_size;
	int queue_front;
	int queue_rear;

	pthread_t  manager_id;
	pthread_t* task_ids;

	int min_task;
	int max_task;
	int busy_num;
	int alive_num;
	int exit_num;

	pthread_mutex_t pool_mutex;
	pthread_mutex_t busy_mutex;
	pthread_cond_t queue_full;
	pthread_cond_t queue_empty;

	int destruct; // 0 -> normal; 1 -> will be destructed
} threadpool;

threadpool* threadpool_create(int min, int max, int queue_size);
int threadpool_destroy(threadpool* pool);

int threadpool_add(threadpool* pool, void(*callback)(void*), void* arg);

int threadpool_busy(threadpool* pool);
int threadpool_alive(threadpool* pool);

void* worker(void* arg);
void* manager(void* arg);

void thread_exit(threadpool* pool);

#endif // THREAD_POOL_H

