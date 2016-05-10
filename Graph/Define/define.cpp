#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 256

typedef struct list
{
	int index;			//	ָ���λ�ã�֮����������еĽ�㶼ֻ��1����ͬ�����
	int weight;			//	Ȩֵ

	struct list *next;
}list, *listptr;

void initlist(list *q)
{
	q->index = 0;
	q->weight = 0;
	q->next = NULL;
}

typedef struct
{
	int vertex;			//	��ʾ����
	listptr first, last;
}Node;

int main()
{
	Node *vertex[MAX_SIZE];
	int from, to, weight, i = 0, flag;
	printf("���������ݣ���from, to, weight��\n");
	
	while(scanf("%d,%d,%d",&from, &to, &weight))
	{
		flag = 0;
		list *temp = (list*)malloc(sizeof(list));
		temp->index = to;
		temp->weight = weight;
		temp->next = NULL;
		
		for(int j=0; j<i; j++)		//	�����ʼλ����ͬ����ô����ÿ�εĽ�β������������
		{
			if(from == vertex[j]->vertex)
			{
				vertex[j]->last->next = temp;
				vertex[j]->last = temp;
				flag = 1;
				break;
			}
		}
		if(0 == flag)				//	���û����ͬ�ģ�����������������
		{
			vertex[i] = (Node*)malloc(sizeof(Node));
			vertex[i]->first = vertex[i]->last = 
				(list*)malloc(sizeof(list));	//����ָ��ʱ�����ʼ��
			vertex[i]->vertex = from;
			vertex[i]->last->next = temp;
			vertex[i]->last = temp;
			i++;
		}
		for(int j=0; j<i; j++)		//	�����ʼλ����ͬ����ô����ÿ�εĽ�β������������
		{
			if(from == vertex[j]->vertex)
			{
				vertex[j]->last->next = temp;
				vertex[j]->last = temp;
				flag = 1;
				break;
			}
		}
	}

	//	�Դ�źõĶ��н������
	list *temp;
	printf("\n���Ϊ��\n");
	for(int j = 0; j < i; j++)
	{
		temp = vertex[j]->first->next;
		printf("%d", vertex[j]->vertex);
		while(NULL != temp)
		{
			printf(" -> %d[%d]", temp->index, temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}

	printf("\n");
	system("pause");
	return 0;
}