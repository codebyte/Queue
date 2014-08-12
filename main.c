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

	qInsert(&q1, &p1);
	qInsert(&q1, &p2);
	qInsert(&q1, &p2);

	printf("\nObj Count : %d", q1.qCount);

	return (0);
}

