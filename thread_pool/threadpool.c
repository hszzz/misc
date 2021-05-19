#include "threadpool.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

threadpool* threadpool_create(int min, int max, int queue_size) {
	threadpool* pool = (threadpool*)malloc(sizeof(threadpool));

	do {
		if (pool == NULL)
			break;
		pool->task_ids = (pthread_t*)malloc(sizeof(pthread_t) * max);
		if (pool->task_ids == NULL)
			break;
		memset(pool->task_ids, 0, sizeof(pthread_t) * max);
		pool->min_task = min;
		pool->max_task = max;

		pool->busy_num  = 0;
		pool->alive_num = min;
		pool->exit_num  = 0;

		if ((pthread_mutex_init(&pool->pool_mutex, NULL) != 0) ||
			(pthread_mutex_init(&pool->busy_mutex, NULL) != 0) || 
			(pthread_cond_init(&pool->queue_not_full, NULL)  != 0) ||
			(pthread_cond_init(&pool->queue_not_empty, NULL) != 0)) {
			break;
		}

		pool->tasks = (task*)malloc(sizeof(task) * queue_size);
		pool->queue_capacity = queue_size;
		pool->queue_size = 0;
		pool->queue_front = 0;
		pool->queue_rear = 0;

		pool->destruct = 0;

		pthread_create(&pool->manager_id, NULL, manager, pool);
		int i = 0;
		for (i; i<min; i++) {
			pthread_create(&pool->task_ids[i], NULL, worker, pool);
		}

		return pool;
	} while(0);

	// error!
	if (pool && pool->task_ids) free(pool->task_ids);
	if (pool && pool->tasks) free(pool->tasks);
	if (pool) free(pool);

	return NULL;
}

int threadpool_destroy(threadpool* pool) {
	int ret = -1;

	if (pool != NULL) {
		int i = 0;

		pool->destruct = 1;
		pthread_join(pool->manager_id, NULL);

		for (i; i<pool->alive_num; i++) {
			pthread_cond_signal(&pool->queue_not_empty);
		}

		if (pool->tasks) 
			free(pool->tasks);

		if (pool->task_ids) 
			free(pool->task_ids);

		pthread_mutex_destroy(&pool->pool_mutex);
		pthread_mutex_destroy(&pool->busy_mutex);
		pthread_cond_destroy(&pool->queue_not_full);
		pthread_cond_destroy(&pool->queue_not_empty);

		free(pool);
		pool = NULL;

		ret = 0;
	} 

	return ret;
}

void threadpool_add(threadpool* pool, void(*callback)(void*), void* arg) {
	pthread_mutex_lock(&pool->pool_mutex);

	// task_queue is full
	while ((pool->queue_size == pool->queue_capacity) && (!pool->destruct)) {
		pthread_cond_wait(&pool->queue_not_full, &pool->pool_mutex);
	}

	if (pool->destruct) {
		pthread_mutex_unlock(&pool->pool_mutex);
		return;
	}

	pool->tasks[pool->queue_rear].callback = callback;
	pool->tasks[pool->queue_rear].arg = arg;

	pool->queue_rear = (pool->queue_rear + 1) % pool->queue_capacity;
	pool->queue_size++;

	// sent signal to all worker thread 
	pthread_cond_signal(&pool->queue_not_empty);
	pthread_mutex_unlock(&pool->pool_mutex);
}

int threadpool_busy(threadpool* pool) {
	int ret = 0;

	pthread_mutex_lock(&pool->busy_mutex);
	ret = pool->busy_num;
	pthread_mutex_unlock(&pool->busy_mutex);
	
	return ret;
}

int threadpool_alive(threadpool* pool) {
	int ret = 0;

	pthread_mutex_lock(&pool->pool_mutex);
	ret = pool->alive_num;
	pthread_mutex_unlock(&pool->pool_mutex);
	
	return ret;
}

void* manager(void* arg) {
	threadpool* pool = (threadpool*)arg;

	while (!pool->destruct) {
		sleep(3);

		pthread_mutex_lock(&pool->pool_mutex);
		int queue_size = pool->queue_size;
		int alive_num  = pool->alive_num;
		int busy_num   = pool->busy_num;
		pthread_mutex_unlock(&pool->pool_mutex);

		// add thread
		if ((queue_size > alive_num) && (alive_num < pool->max_task)) {
			pthread_mutex_lock(&pool->pool_mutex);

			int i = 0;
			int counter = 0;
			for (i; (i<pool->max_task) && (counter < 2) &&
				   	(pool->alive_num < pool->max_task); i++) {
				if (pool->task_ids[i] == 0) {
					pthread_create(&pool->task_ids[i], NULL, worker, pool);
					counter++;
					pool->alive_num++;
				}
			}
			
			pthread_mutex_unlock(&pool->pool_mutex);
		}

		// remove thread
		if ((busy_num * 2 < alive_num) && (alive_num > pool->min_task)) {
			int i = 0;
			
			pthread_mutex_lock(&pool->pool_mutex);
			pool->exit_num = 1;
			pthread_mutex_unlock(&pool->pool_mutex);

			pthread_cond_signal(&pool->queue_not_empty);
		}
	}
	return NULL;
}

void* worker(void* arg) {
	threadpool* pool = (threadpool*)arg;

	while (1) {
		pthread_mutex_lock(&pool->pool_mutex);

		while ((pool->queue_size == 0) && (!pool->destruct)) {
			pthread_cond_wait(&pool->queue_not_empty, &pool->pool_mutex);

			if (pool->exit_num > 0) {
				pool->exit_num--;
				if (pool->alive_num > pool->min_task) {
					pool->alive_num--;
					pthread_mutex_unlock(&pool->pool_mutex);
					thread_exit(pool);
				}
			}
		}

		if (pool->destruct) {
			pthread_mutex_unlock(&pool->pool_mutex);
			thread_exit(pool);
		}

		task t;
		t.callback = pool->tasks[pool->queue_front].callback;
		t.arg = pool->tasks[pool->queue_front].arg;

		pool->queue_front = (pool->queue_front + 1) % pool->queue_capacity;
		pool->queue_size--;

		pthread_cond_signal(&pool->queue_not_full);
		pthread_mutex_unlock(&pool->pool_mutex);
		
		// (busy_num++) increase the number of busy thread 
		pthread_mutex_lock(&pool->busy_mutex);
		pool->busy_num++;
		pthread_mutex_unlock(&pool->busy_mutex);

		t.callback(t.arg);
		free(t.arg);
		t.arg = NULL;

		pthread_mutex_lock(&pool->busy_mutex);
		pool->busy_num--;
		pthread_mutex_unlock(&pool->busy_mutex);
	}

	return NULL;
}
					
void thread_exit(threadpool* pool) {
	int i = 0;
	pthread_t tid = pthread_self();

	for (i; i<pool->max_task; i++) {
		if (pool->task_ids[i] == tid) {
			pool->task_ids[i] = 0;
			break;
		}
	}

	pthread_exit(NULL);
}

