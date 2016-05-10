#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

//	线索存储标志位
//	Link(0)：表示指向左右孩子的指针
//	Thread(1)：表示指向前驱后继的线索
typedef enum {Link, Thread} PointerTag;

typedef struct BiTNode
{
	char data;
	PointerTag ltag, rtag;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//	始终指向刚刚访问过的结点
BiTNode *pre;

//	创建一棵二叉树，前序遍历的方式输入数据
void CreateBiTree(BiTree *T)
{
	char c;
	scanf("%c", &c);
	if( ' ' == c )
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = c;
		(*T)->ltag = Link;
		(*T)->rtag = Link;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

//	访问二叉树结点的具体操作
void visit(char c, int level)
{
	printf("%c 位于第 %d 层\n", c, level);
}

//	前序遍历二叉树
void PreOrderTraverse(BiTree T, int level)
{
	if( T )
	{
		visit(T->data, level);
		PreOrderTraverse(T->lchild, level+1);
		PreOrderTraverse(T->rchild, level+1);
	}
}

void visit0(char c)
{
	printf("%c", c);
}

//	中序遍历二叉树，非递归
void InOrderTraverse(BiTree T)
{
	BiTree p;
	p = T->lchild;

	while(p != T)
	{
		while(p->ltag == Link)
		{
			p = p->lchild;
		}	// 每次找到最先输出的字符
		visit0(p->data);
		while(p->rtag == Thread && p->rchild != T)
		{
			p = p->rchild;	//	每次从叶子结点去找到下一个需要输出的位置
			visit0(p->data);
		}

		p = p->rchild;
	}
	printf("\n");
}

//	中序遍历线索化
void InThreading(BiTree T)
{
	if( T )
	{
		InThreading(T->lchild);		//	递归左孩子线索化

		if( !T->lchild )	//	如果该节点没有左孩子，设置ltag为Thread，
							//	并把lchild指向刚刚访问的结点
		{
			T->ltag = Thread;
			T->lchild = pre;
		}

		if( !pre->rchild )
		{
			pre->rtag = Thread;
			pre->rchild = T;
		}

		pre = T;

		InThreading(T->rchild);		//	递归又孩子线索化
	}
}

void InOrderThreading( BiTree *p, BiTree T )
{
	*p = (BiTree)malloc(sizeof(BiTNode));
	(*p)->ltag = Link;
	(*p)->rtag = Thread;
	(*p)->rchild = *p;
	if( !T )
	{
		(*p)->lchild = *p;
	}
	else
	{
		(*p)->lchild = T;
		pre = *p;
		InThreading(T);
		pre->rchild = *p;
		pre->rtag = Thread;
		(*p)->rchild = pre;
	}
}

int main()
{
	int level = 1;
	BiTree p, T = NULL;

	CreateBiTree(&T);

	InOrderThreading(&p, T);
//	PreOrderTraverse(T, level);

	InOrderTraverse(p);

	system("pause");
	return 0;
}