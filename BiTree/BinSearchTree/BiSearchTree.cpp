#include "BiSearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void MakeEmpty(SearchTree T)	//	清空二叉树
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

Position FindMin(SearchTree T)		//	查找最小数
{
	if(NULL == T)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(SearchTree T)		//	查找最大数
{
	if(NULL == T)
		return NULL;
	while(T->Right != NULL)
		T = T->Right;				//	其实过程和查找最小数一样，一个是找最左边的树，一个是找最右边的树
	return T;
}

Position Insert(Element x, SearchTree &T)
{
	if(NULL == T)
	{
		T = (SearchTree)malloc(sizeof(SearchNode));
		if(!T)
		{
			printf("内存分配失败\n");
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
		//	二叉搜索树的关键，小的放左边，大的放右边，是一个递归的过程
		//	那输入的数据重复呢？不放入二叉树中？
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
		//	删除操作的关键，左右子树都有的话，则需要将右子树中最小的元素放入删除位置中，再删除最小元素的位置
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

void InOrderTraverse(SearchTree T)	//	前序遍历
{
	if(T)
	{
		printf("%d ", T->data);
		InOrderTraverse(T->Left);
		InOrderTraverse(T->Right);
	}
}