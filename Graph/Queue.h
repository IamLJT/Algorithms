#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct Node
{
	int data;
	struct Node *next;
}Node, *QueuePrt;
typedef struct
{
	QueuePrt front, rear;	//	��ͷ��βָ��
}Queue;
void InitQueue(Queue *q);	//	��ʼ������
bool IsEmpty(Queue *q);		//	�ж϶����Ƿ�Ϊ��
void EnQueue(Queue *q, int Element);	//	���
void DeQueue(Queue *q, int *e);			//	����

#endif