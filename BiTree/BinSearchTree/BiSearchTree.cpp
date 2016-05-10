#include "BiSearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void MakeEmpty(SearchTree T)	//	��ն�����
{
	if(T)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
}

bool IsEmpty(SearchTree T)	
{
	if(T == NULL)
		return true;
	else
		return false;
}

bool Find(Element x, SearchTree T)
{
	if(NULL == T)
		return false;
	else if(x < T->data)
		return Find(x, T->Left);
	else if(x > T->data)
		return Find(x, T->Right);
	return true;
}

Position FindMin(SearchTree T)		//	������С��
{
	if(NULL == T)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(SearchTree T)		//	���������
{
	if(NULL == T)
		return NULL;
	while(T->Right != NULL)
		T = T->Right;				//	��ʵ���̺Ͳ�����С��һ����һ����������ߵ�����һ���������ұߵ���
	return T;
}

Position Insert(Element x, SearchTree &T)
{
	if(NULL == T)
	{
		T = (SearchTree)malloc(sizeof(SearchNode));
		if(!T)
		{
			printf("�ڴ����ʧ��\n");
			exit(1);
		}
		T->data = x;
		T->Left = T->Right = NULL;
	}
	else
	{
		if(x < T->data)
			T->Left = Insert(x, T->Left);
		else if(x > T->data)
			T->Right = Insert(x, T->Right);
		//	�����������Ĺؼ���С�ķ���ߣ���ķ��ұߣ���һ���ݹ�Ĺ���
		//	������������ظ��أ�������������У�
	}
	return T;
}

Position Delete(Element x, SearchTree &T)
{
	SearchTree temp = NULL;
	SearchTree tp = NULL;
	if(NULL == T)
		return NULL;
	else if(x < T->data)
		T->Left = Delete(x, T->Left);
	else if(x > T->data)
		T->Right = Delete(x, T->Right);
	else if(T->Left && T->Right)
	{
		temp = FindMin(T->Right);
		T->data = temp->data;
		T->Right = Delete(temp->data, T->Right);
		//	ɾ�������Ĺؼ��������������еĻ�������Ҫ������������С��Ԫ�ط���ɾ��λ���У���ɾ����СԪ�ص�λ��
	}
	else
	{
		tp = T;
		if(NULL == T->Left)
			T = T->Right;
		if(NULL == T->Right)
			T = T->Left;
		free(tp);
	}
	return T;
}

void InOrderTraverse(SearchTree T)	//	ǰ�����
{
	if(T)
	{
		printf("%d ", T->data);
		InOrderTraverse(T->Left);
		InOrderTraverse(T->Right);
	}
}