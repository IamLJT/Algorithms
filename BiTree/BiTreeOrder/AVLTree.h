#ifndef _AVLTREE_H
#define _AVLTREE_H

typedef int Element;
typedef struct Node
{
	Element data;
	struct Node *left, *right;
	int Height;
}AvlNode, *AvlTree, *Position;

void MakeEmpty(AvlTree &T);		//	清空平衡二叉树
bool IsEmpty(AvlTree T);		//	判断树是否为空
bool Find(Element x, AvlTree T);//	查找元素
Position FindMin(AvlTree T);	//	查找最小元素
Position FindMax(AvlTree T);	//	查找最大元素
AvlTree Insert(Element x, AvlTree &T);//	插入元素
Position SingleRotationWithLeft(AvlTree k2);	//	向左单旋转
Position SingleRotationWithRight(AvlTree k2);	//	向右单旋转
Position DoubleRotationWithLeft(AvlTree k3);	//
Position DoubleRotationWithRight(AvlTree k3);
int MAX(int a, int b);
int Height(Position p);			//	返回节点的高度
void InOrderTraverse(AvlTree T);//	前序遍历树

#endif