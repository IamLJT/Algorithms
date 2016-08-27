#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct Node
{
	int data;
	struct Node *next;
}Node, *QueuePrt;
typedef struct
{
	QueuePrt front, rear;	//	队头、尾指针
}Queue;
void InitQueue(Queue *q);	//	初始化队列
bool IsEmpty(Queue *q);		//	判断队列是否为空
void EnQueue(Queue *q, int Element);	//	入队
void DeQueue(Queue *q, int *e);			//	出队

#endif