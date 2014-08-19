#include <malloc.h>
#include <pthread.h>
#include <string.h>
#include "queue.h"
#include "common.h"


void qInit(queueObj_t *qObj)
{
	qObj->qHead = qObj->qTail = NULL;
	pthread_mutex_init(&qObj->qMutex, NULL);
}


void qInsert(queueObj_t *qObj, void *data)
{
	if (!qObj || !data) {	
		return;
	}
	
	Q_LOCK(&qObj->qMutex);

	NODE *node = allocate_node(data);

	if (!qObj->qHead) {
		qObj->qHead = qObj->qTail = node;
		++qObj->qCount;

	} else {

		qObj->qTail->next = node;
		node->prev = qObj->qTail;
		qObj->qTail = node;
		++qObj->qCount;
	}			

	Q_UNLOCK(&qObj->qMutex);
}

void qRemove(queueObj_t *qObj, void *data, size_t nSize)
{
	Q_LOCK(&qObj->qMutex);

	NODE *node = qObj->qHead;

	if (!qObj->qHead || !qObj->qTail) {
		goto end;
	}


	if(qObj->qHead == qObj->qTail) {

		node  = qObj->qHead;
		qObj->qHead = qObj->qTail = NULL;
		--qObj->qCount;

	} else {

		qObj->qHead 		= qObj->qHead->next;
		node->next 		= NULL;
		qObj->qHead->prev 	= NULL;
		--qObj->qCount;
	}
	
	if(data) {
		memcpy(data, node->data, nSize);
	}


	end:
		FREE(node);
		Q_UNLOCK(&qObj->qMutex);
}

NODE *allocate_node(void *data)
{
	NODE *node  = (NODE *)calloc(1,
						sizeof (NODE));
	node->next = node->prev = 0;
	node->data = data;	

	return (node);
}


void qDestroy(queueObj_t *qObj) {

	if(!qObj) {
		return;
	}

	Q_LOCK(&qObj->qMutex);
	
	NODE *node = NULL;

	while(qObj->qHead != NULL) {

		node 			= qObj->qHead;
		qObj->qHead             = qObj->qHead->next;

		FREE(node);
	}

	qObj->qTail = qObj->qHead = 0;

	Q_UNLOCK(&qObj->qMutex);
	pthread_mutex_destroy(&qObj->qMutex);
}


void printQ(queueObj_t *qObj, workCB func)
{

	NODE *node = qObj->qHead;

	if(!node) {
		return;
	}

	while(node != NULL) {
		func(node->data);
		node = node->next;
	}
}

