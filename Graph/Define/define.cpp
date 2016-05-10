#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 256

typedef struct list
{
	int index;			//	指向的位置，之后队列中所有的结点都只有1个共同的起点
	int weight;			//	权值

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
	int vertex;			//	表示顶点
	listptr first, last;
}Node;

int main()
{
	Node *vertex[MAX_SIZE];
	int from, to, weight, i = 0, flag;
	printf("请输入数据：（from, to, weight）\n");
	
	while(scanf("%d,%d,%d",&from, &to, &weight))
	{
		flag = 0;
		list *temp = (list*)malloc(sizeof(list));
		temp->index = to;
		temp->weight = weight;
		temp->next = NULL;
		
		for(int j=0; j<i; j++)		//	如果起始位置相同，那么就在每次的结尾处加上这个结点
		{
			if(from == vertex[j]->vertex)
			{
				vertex[j]->last->next = temp;
				vertex[j]->last = temp;
				flag = 1;
				break;
			}
		}
		if(0 == flag)				//	如果没有相同的，则继续往下添加数组
		{
			vertex[i] = (Node*)malloc(sizeof(Node));
			vertex[i]->first = vertex[i]->last = 
				(list*)malloc(sizeof(list));	//定义指针时必须初始化
			vertex[i]->vertex = from;
			vertex[i]->last->next = temp;
			vertex[i]->last = temp;
			i++;
		}
		for(int j=0; j<i; j++)		//	如果起始位置相同，那么就在每次的结尾处加上这个结点
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

	//	对存放好的队列进行输出
	list *temp;
	printf("\n输出为：\n");
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