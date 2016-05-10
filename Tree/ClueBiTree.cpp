#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

//	�����洢��־λ
//	Link(0)����ʾָ�����Һ��ӵ�ָ��
//	Thread(1)����ʾָ��ǰ����̵�����
typedef enum {Link, Thread} PointerTag;

typedef struct BiTNode
{
	char data;
	PointerTag ltag, rtag;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//	ʼ��ָ��ոշ��ʹ��Ľ��
BiTNode *pre;

//	����һ�ö�������ǰ������ķ�ʽ��������
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

//	���ʶ��������ľ������
void visit(char c, int level)
{
	printf("%c λ�ڵ� %d ��\n", c, level);
}

//	ǰ�����������
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

//	����������������ǵݹ�
void InOrderTraverse(BiTree T)
{
	BiTree p;
	p = T->lchild;

	while(p != T)
	{
		while(p->ltag == Link)
		{
			p = p->lchild;
		}	// ÿ���ҵ�����������ַ�
		visit0(p->data);
		while(p->rtag == Thread && p->rchild != T)
		{
			p = p->rchild;	//	ÿ�δ�Ҷ�ӽ��ȥ�ҵ���һ����Ҫ�����λ��
			visit0(p->data);
		}

		p = p->rchild;
	}
	printf("\n");
}

//	�������������
void InThreading(BiTree T)
{
	if( T )
	{
		InThreading(T->lchild);		//	�ݹ�����������

		if( !T->lchild )	//	����ýڵ�û�����ӣ�����ltagΪThread��
							//	����lchildָ��ոշ��ʵĽ��
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

		InThreading(T->rchild);		//	�ݹ��ֺ���������
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