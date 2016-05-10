#ifndef _AVLTREE_H
#define _AVLTREE_H

typedef int Element;
typedef struct Node
{
	Element data;
	struct Node *left, *right;
	int Height;
}AvlNode, *AvlTree, *Position;

void MakeEmpty(AvlTree &T);		//	���ƽ�������
bool IsEmpty(AvlTree T);		//	�ж����Ƿ�Ϊ��
bool Find(Element x, AvlTree T);//	����Ԫ��
Position FindMin(AvlTree T);	//	������СԪ��
Position FindMax(AvlTree T);	//	�������Ԫ��
AvlTree Insert(Element x, AvlTree &T);//	����Ԫ��
Position SingleRotationWithLeft(AvlTree k2);	//	������ת
Position SingleRotationWithRight(AvlTree k2);	//	���ҵ���ת
Position DoubleRotationWithLeft(AvlTree k3);	//
Position DoubleRotationWithRight(AvlTree k3);
int MAX(int a, int b);
int Height(Position p);			//	���ؽڵ�ĸ߶�
void InOrderTraverse(AvlTree T);//	ǰ�������

#endif