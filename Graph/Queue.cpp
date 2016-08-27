#include "Queue.h"
#include "stdlib.h"

void InitQueue(Queue *q)
{
	q->front = q->rear = (QueuePrt)malloc(sizeof(Node));
	q->front->next = NULL;
}

bool IsEmpty(Queue *q)
{
	if(q->rear == q->front)
		return true;
	return false;
}

void EnQueue(Queue *q, int Element)
{
	QueuePrt p;
	p = (QueuePrt)malloc(sizeof(Node));
	p->data = Element;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}

void DeQueue(Queue *q, int *e)
{
	QueuePrt p;
	if(q->front == q->rear)
		return;
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	if(q->rear == p)
		q->rear = q->front;
	free(p);
}