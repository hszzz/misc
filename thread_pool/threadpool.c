#include "threadpool.h"

#include <string.h>
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
			(pthread_cond_init(&pool->queue_full, NULL)  != 0) ||
			(pthread_cond_init(&pool->queue_empty, NULL) != 0)) {
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
}

