#include <stdio.h>
#include <stdlib.h>

#define ERROR	0
#define OK		1

typedef char	ElemType;
typedef int		Status;

typedef struct DualNode
{
	ElemType data;
	struct DualNode *prior;
	struct DualNode *next;
}DualNode, *DuLinkList;

Status InitList(DuLinkList *L)
{
	DualNode *p, *q;
	int i;

	*L = (DuLinkList)malloc(sizeof(DualNode));
	if(!(*L))
	{
		return ERROR;
	}

	(*L)->next = (*L)->prior = NULL;
	p = (*L);		//头结点

	for(i=0; i < 26; i++)
	{
		q = (DualNode *)malloc(sizeof(DualNode));
		if(!q)
			return ERROR;

		q->data = 'A'+i;
		q->prior = p;
		q->next = p->next;
		p->next = q;
		
		p = q;
	}	//构成双向链表

	q->next = (*L)->next;
	(*L)->next->prior = q;	//构成循环

	return OK;
}

void Caesar(DuLinkList *L, int i)
{
	
	if(i > 0)
	{
		(*L) = (*L)->next ;
		(*L) = (*L)->prior;
		do
		{
			(*L) = (*L)->prior;
			
		}while(--i);
	}
	if(i < 0)
	{
		do
		{
			(*L) = (*L)->next;
		}while(++i);
	}
}

int main()
{
	DuLinkList L;
	int i,n;

	InitList(&L);

	printf("请输入一个整数：");
	while(scanf("%d", &n))
	{
		//printf("\n");
		Caesar(&L, n%26);

		for(i=0; i<26; i++)
		{
			L = L->next;
			printf("%c", L->data);
			
		}
		printf("\n");
		printf("请输入一个整数：");
	}
	system("pause");
	return 0;
}