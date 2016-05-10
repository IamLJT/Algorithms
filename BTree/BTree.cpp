#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

//在p->node[1]....p->node[keynum]中查找k所处的位置p->node[i].key <= k < p->node[i+1].key
int Search(BTree p, int k)
{
	int i = 0;
	int j;
	for(j=1; j<=p->keynum; ++j)
		if(k>=p->node[j].key)	//	如果k大于p指向的结点的第j个位置的关键字，记录下j
			i = j;
	return i;
}

//在M阶B树T上查找关键字K,返回结果Result  
//查找成功,tag = 1,pt指向包函关键字K的结点,i为K在结点中的位置  
//查找失败,tag = 0,pt指向K应插入的结点,i...i+1之间插入K  
Result SearchBTree(BTree T, int k)
{
	Result r;					//	查找的结果
	bool found = false;			//	是否查找到的标志，初始化为未找到
	int i = 0;					//	用于记录位置，如查找成功则是k所在结点的第i个位置，
								//	查找失败则是k应该插入的结点的第i个位置
	BTree p = T;				//	初始化为待查找的结点
	BTree q = NULL;				//	记录父节点，初始化为NULL
	while(p && !found)			//	待查找的结点不为NULL，且未找到进行循环
	{
		i = Search(p, k);		//	进行查找
		if(i > 0 && p->node[i].key == k)
			found = true;
		else
		{
			q = p;				//	记录下当前节点，此节点是p->node[i].ptr所指结点的父节点
			p = p->node[i].ptr;	//	p赋值为它的子树，继续进行循环
		}
	}
	r.i = i;					//	如如查找成功则是k所在节点的第i个位置
								//	查找失败则是k应该插入的结点的第i个位置
	if(found)
	{
		r.pt = p;				//	记录下所在的结点的指针
		r.tag = 1;				//	标记为查找成功
	}
	else
	{
		r.pt = q;				//	记录下要插入的结点
		r.tag = 0;				//	标记为查找不成功
	}
	return r;
}

//将key插入到*q所指向的结点的第i + 1个位置  
void Insert(BTree *q, int i, int key, BTree ap)
{
	int j;
	for(j = (*q)->keynum; j > i; --j)	//	静态数组的插入，第i个位置之后的所有元素向后移一位
		(*q)->node[j+1] = (*q)->node[j];
	(*q)->node[i+1].key = key;
	(*q)->node[i+1].ptr = ap;
	(*q)->node[i+1].recptr = key;
	(*q)->keynum++;
}

//在M阶B树T上，在q所指向的节点第i与i + 1的中间插入key  
//若引起结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树 
void InsertBTree(BTree *T, int key, BTree q, int i)
{
	BTree ap = NULL;
	int s;
	int rx = key;						//	如果进行分裂，rx记录的是需要插入父节点的值
	bool finished = false;				//	记录插入是否完成，初始化为未完成
	while(q && !finished)
	{
		Insert(&q, i, rx, ap);
		if(q->keynum < M)
			finished = true;	
		else
		{
			//	若超过BTree的阶，则进行分裂
			s = (M+1)/2;
			rx = q->node[s].recptr;
			Split(&q, &ap);
			q = q->parent;
			if(q)
				i = Search(q, key);		//	查找key应该在父节点中插入的位置，在该位置插入r
		}
	}
	if(!finished)						//	如果树是空树或已经分裂到根节点
		NewRoot(T, rx, ap);				//	生成新节点原来的T和ap作为子树
}

//	将结点q分裂为两个结点，前一半保留，后一半移入新生结点ap
void Split(BTree *q, BTree *ap)
{
	*ap = (BTree)malloc(sizeof(BTNode));
	int s = (M+1)/2;
	(*ap)->node[0].ptr = (*q)->node[s].ptr;
	for(int i=s+1; i<=M; ++i)			//	将后一半移入新生结点ap
	{
		(*ap)->node[i-s] = (*q)->node[i];
		if((*ap)->node[i-s].ptr)
			(*ap)->node[i-s].ptr->parent = *ap;
	}
	(*ap)->parent = (*q)->parent;
	(*ap)->keynum = M - s;
	(*q)->keynum = s - 1;				//	q的前一半保留，修改keynum
}

//生成新的根结点T，原T和ap为子树指针
void NewRoot(BTree *T, int key, BTree ap)
{
	BTree temp = (BTree)malloc(sizeof(BTNode));
	temp->node[0].ptr = *T;
	*T = temp;
	if((*T)->node[0].ptr)
		(*T)->node[0].ptr->parent = *T;
	(*T)->parent = NULL;
	(*T)->keynum = 1;
	(*T)->node[1].key = key;
	(*T)->node[1].ptr = ap;
	(*T)->node[1].recptr = key;
	if((*T)->node[1].ptr)
		(*T)->node[1].ptr->parent = (*T);
}

//打印出当前结点c的第i个位置的key  
void print(BTNode c,int i)  
{  
    printf("(%d)\n",c.node[i].key);  
}  