#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTreeOrder(BiTree *T,int n)
{
	if(*T==NULL)
	{
		*T = (BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data = n;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
	}
	else
	{
		if(n>(*T)->data)
			CreateBiTreeOrder(&(*T)->rchild, n);
		if(n<(*T)->data)
			CreateBiTreeOrder(&(*T)->lchild, n);
	}
}

//	�ݹ���Ҷ���������T���Ƿ����key
//	ָ��fָ��T��˫�ף����ʼֵΪNULL
//	�����ҳɹ�����pָ�������Ԫ�ؽ�㣬������TRUE
//	����ָ��pָ�����·���Ϸ��ʵ����һ����㣬������FALSE
typedef bool Status;
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
	if(!T)		//	���Ҳ��ɹ�
	{
		*p = f;
		return false;
	}
	else if(key == T->data)
	{
		*p = T;
		return true;
	}
	else if(key < T->data)
	{
		return SearchBST(T->lchild, key, T, p);
	}
	else if(key > T->data)
	{
		return SearchBST(T->rchild, key, T, p);
	}
}

Status InsertBST(BiTree *T, int key)
{
	BiTree p, s;
	if(!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;

		if(!p)				//	���Ҳ���
		{
			*T = s;			//	����sΪ�µĸ��ڵ�
		}
		else if(key < p->data)
		{
			p->lchild = s;	//	����sΪ����
		}
		else if(key > p->data)
		{
			p->rchild = s;	//	����sΪ�Һ���
		}
		return true;
	}
	else
	{
		return false;		//	�������йؼ�����ͬ�Ľ�㣬���ٲ���
	}
}

void isEmpty(BiTree s, BiTree o)
{
	if(s->rchild)
		isEmpty(s->rchild, o);
	else
		o = s;
}

Status DeleteBST(BiTree *T, int key)
{
	BiTree p, s, o = NULL;
	if(SearchBST(*T, key, NULL, &p))
	{
		if(p->lchild==NULL)
		{
			p=p->rchild;
		}
		else
		{
			isEmpty(p->lchild, o);
			p->data = o->data;
			o = o->lchild;
		}
		return true;
	}
	return false;
}

//	���ʶ��������ľ������
void visit(int c)
{
	printf("%d ", c);
}

//	����������
void PreOrderTraverse(BiTree T)
{
	if( T )
	{
		PreOrderTraverse(T->lchild);
		visit(T->data);
		PreOrderTraverse(T->rchild);
	}
}

int main()
{
	BiTree T = NULL;
	int n, level=1;
	while(scanf("%d", &n))
		CreateBiTreeOrder(&T, n);

	PreOrderTraverse(T);

	system("pause");
	return 0;
}