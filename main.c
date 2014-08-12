#include <stdio.h>
#include <string.h>
#include "queue.h"

typedef struct payload {
	workCB func;
	void *arg;
}payload_t;	

void* work(void *arg)
{
	printf("\n Work \n");
	
	return (NULL);
}

void* print(void *data)
{
	payload_t *t = (payload_t *)data;
	printf("\n Payload : %s", (char*)t->arg);
}

int main(void)
{

	payload_t p1, p2, p3;
	queueObj_t q1;

	memset(&q1, 0, sizeof(queueObj_t));

	p1.func = work;
	p1.arg  = "SUJEET";


	p2.func = work;
	p2.arg  = "JOG";

	p3.func = work;
	p3.arg  = "SUMEDHA";

	qInit(&q1);

	qInsert(&q1, &p1);
	qInsert(&q1, &p2);
	qInsert(&q1, &p3);

	printf("\nObj Count : %d", q1.qCount);
	printQ(&q1, print);

	qInsert(&q1, &p2);

	printf("\nBefore Destroy Obj Count : %d", q1.qCount);
	printQ(&q1, print);

	qDestroy(&q1);
	printQ(&q1, print);
	printf("\nAfter Destroy Obj Count : %d", q1.qCount);

	return (0);
}


