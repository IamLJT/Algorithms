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

//	递归查找二叉排序树T中是否存在key
//	指针f指向T的双亲，其初始值为NULL
//	若查找成功，则p指向该数据元素结点，并返回TRUE
//	否则指针p指向查找路径上访问的最后一个结点，并返回FALSE
typedef bool Status;
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
	if(!T)		//	查找不成功
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

		if(!p)				//	查找不到
		{
			*T = s;			//	插入s为新的根节点
		}
		else if(key < p->data)
		{
			p->lchild = s;	//	插入s为左孩子
		}
		else if(key > p->data)
		{
			p->rchild = s;	//	插入s为右孩子
		}
		return true;
	}
	else
	{
		return false;		//	树中已有关键字相同的结点，不再插入
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

//	访问二叉树结点的具体操作
void visit(int c)
{
	printf("%d ", c);
}

//	遍历二叉树
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