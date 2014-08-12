#ifndef _QUEUE_H
#define _QUEUE_H

#include <pthread.h>

typedef void* (*workCB)(void *arg);


/* Queue node */
typedef struct node
{
	void  *data;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct queueObj
{
	NODE *qHead;
	NODE *qTail;
	int qCount;
	pthread_mutex_t qMutex;
}queueObj_t;	


void qInsert(queueObj_t *qObj, void *data);
void qRemove(queueObj_t *qObj, void *data, size_t nSize);
void qDestroy(queueObj_t *qObj);


void printQueue(queueObj_t *qObj);
NODE *allocate_node(void *data);

#endif
