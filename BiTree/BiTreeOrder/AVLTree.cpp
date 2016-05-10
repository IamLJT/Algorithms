#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void MakeEmpty(AvlTree &T)
{
	if(T == NULL)
		return;
	MakeEmpty(T->left);
	MakeEmpty(T->right);
	free(T);
	T = NULL;
}

bool IsEmpty(AvlTree T)
{
	return T == NULL ? true : false;
}

bool Find(Element x, AvlTree T)
{
	if(T == NULL)
		return false;
	else if(x < T->data)	//	如果元素小于当前节点往左继续寻找
		return Find(x, T->left);
	else if(x > T->data)	
		return Find(x, T->right);
	return true;
}

Position FindMin(AvlTree T)	//	查找最小值
{
	if(T == NULL)
		return NULL;
	else if(T->left == NULL)
		return T;
	else
		FindMin(T->left);
}

Position FindMax(AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->right == NULL)
		return T;
	else
		FindMax(T->right);
}

AvlTree Insert(Element x, AvlTree &T)
{
	if(T == NULL)
	{
		T = (AvlTree)malloc(sizeof(AvlNode));
		if(!T)
		{
			printf("内存分配失败，程序即将退出\n");
			exit(1);
		}
		T->data = x;
		T->Height = 0;
		T->left = T->right = NULL;
	}
	else if(x < T->data)
	{
		T->left = Insert(x, T->left);
		if(Height(T->left) - Height(T->right) == 2)
		{
			if(x < T->left->data)
				T = SingleRotationWithLeft(T);
			else
				T = DoubleRotationWithLeft(T);
		}
	}
	else if(x > T->data)
	{
		T->right = Insert(x, T->right);
		if(Height(T->right) - Height(T->left) == 2)
		{
			if(x > T->right->data)
				T = SingleRotationWithRight(T);
			else
				T = DoubleRotationWithRight(T);
		}
	}
	T->Height = MAX(Height(T->left), Height(T->right)) + 1;	//计算节点高度
	return T;
}

Position SingleRotationWithLeft(AvlTree k2)
{
	Position k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->Height = MAX(Height(k2->left), Height(k2->right)) + 1;
	k1->Height = MAX(Height(k1->left), k2->Height) + 1;
	return k1;
}

Position SingleRotationWithRight(AvlTree k2)
{
	Position k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->Height = MAX(Height(k2->left), Height(k2->right)) + 1;
	k1->Height = MAX(Height(k1->right), k2->Height) + 1;
	return k1;
}

Position DoubleRotationWithLeft(AvlTree k3)
{
	k3->left = SingleRotationWithRight(k3->left);
	return SingleRotationWithLeft(k3);
}

Position DoubleRotationWithRight(AvlTree k3)
{
	k3->right = SingleRotationWithLeft(k3->right);
	return SingleRotationWithRight(k3);
}

int Height(Position p)
{
	return p == NULL ? -1 : p->Height;
}

int MAX(int a, int b)
{
	return a > b ? a : b;
}

void InOrderTraverse(AvlTree T)
{
	if(T)
	{
		printf("%d ", T->data);
		InOrderTraverse(T->left);
		InOrderTraverse(T->right);
	}
}