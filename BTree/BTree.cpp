#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

//��p->node[1]....p->node[keynum]�в���k������λ��p->node[i].key <= k < p->node[i+1].key
int Search(BTree p, int k)
{
	int i = 0;
	int j;
	for(j=1; j<=p->keynum; ++j)
		if(k>=p->node[j].key)	//	���k����pָ��Ľ��ĵ�j��λ�õĹؼ��֣���¼��j
			i = j;
	return i;
}

//��M��B��T�ϲ��ҹؼ���K,���ؽ��Result  
//���ҳɹ�,tag = 1,ptָ������ؼ���K�Ľ��,iΪK�ڽ���е�λ��  
//����ʧ��,tag = 0,ptָ��KӦ����Ľ��,i...i+1֮�����K  
Result SearchBTree(BTree T, int k)
{
	Result r;					//	���ҵĽ��
	bool found = false;			//	�Ƿ���ҵ��ı�־����ʼ��Ϊδ�ҵ�
	int i = 0;					//	���ڼ�¼λ�ã�����ҳɹ�����k���ڽ��ĵ�i��λ�ã�
								//	����ʧ������kӦ�ò���Ľ��ĵ�i��λ��
	BTree p = T;				//	��ʼ��Ϊ�����ҵĽ��
	BTree q = NULL;				//	��¼���ڵ㣬��ʼ��ΪNULL
	while(p && !found)			//	�����ҵĽ�㲻ΪNULL����δ�ҵ�����ѭ��
	{
		i = Search(p, k);		//	���в���
		if(i > 0 && p->node[i].key == k)
			found = true;
		else
		{
			q = p;				//	��¼�µ�ǰ�ڵ㣬�˽ڵ���p->node[i].ptr��ָ���ĸ��ڵ�
			p = p->node[i].ptr;	//	p��ֵΪ������������������ѭ��
		}
	}
	r.i = i;					//	������ҳɹ�����k���ڽڵ�ĵ�i��λ��
								//	����ʧ������kӦ�ò���Ľ��ĵ�i��λ��
	if(found)
	{
		r.pt = p;				//	��¼�����ڵĽ���ָ��
		r.tag = 1;				//	���Ϊ���ҳɹ�
	}
	else
	{
		r.pt = q;				//	��¼��Ҫ����Ľ��
		r.tag = 0;				//	���Ϊ���Ҳ��ɹ�
	}
	return r;
}

//��key���뵽*q��ָ��Ľ��ĵ�i + 1��λ��  
void Insert(BTree *q, int i, int key, BTree ap)
{
	int j;
	for(j = (*q)->keynum; j > i; --j)	//	��̬����Ĳ��룬��i��λ��֮�������Ԫ�������һλ
		(*q)->node[j+1] = (*q)->node[j];
	(*q)->node[i+1].key = key;
	(*q)->node[i+1].ptr = ap;
	(*q)->node[i+1].recptr = key;
	(*q)->keynum++;
}

//��M��B��T�ϣ���q��ָ��Ľڵ��i��i + 1���м����key  
//�����������,����˫�������б�Ҫ�Ľ����ѵ���,ʹT����m��B�� 
void InsertBTree(BTree *T, int key, BTree q, int i)
{
	BTree ap = NULL;
	int s;
	int rx = key;						//	������з��ѣ�rx��¼������Ҫ���븸�ڵ��ֵ
	bool finished = false;				//	��¼�����Ƿ���ɣ���ʼ��Ϊδ���
	while(q && !finished)
	{
		Insert(&q, i, rx, ap);
		if(q->keynum < M)
			finished = true;	
		else
		{
			//	������BTree�Ľף�����з���
			s = (M+1)/2;
			rx = q->node[s].recptr;
			Split(&q, &ap);
			q = q->parent;
			if(q)
				i = Search(q, key);		//	����keyӦ���ڸ��ڵ��в����λ�ã��ڸ�λ�ò���r
		}
	}
	if(!finished)						//	������ǿ������Ѿ����ѵ����ڵ�
		NewRoot(T, rx, ap);				//	�����½ڵ�ԭ����T��ap��Ϊ����
}

//	�����q����Ϊ������㣬ǰһ�뱣������һ�������������ap
void Split(BTree *q, BTree *ap)
{
	*ap = (BTree)malloc(sizeof(BTNode));
	int s = (M+1)/2;
	(*ap)->node[0].ptr = (*q)->node[s].ptr;
	for(int i=s+1; i<=M; ++i)			//	����һ�������������ap
	{
		(*ap)->node[i-s] = (*q)->node[i];
		if((*ap)->node[i-s].ptr)
			(*ap)->node[i-s].ptr->parent = *ap;
	}
	(*ap)->parent = (*q)->parent;
	(*ap)->keynum = M - s;
	(*q)->keynum = s - 1;				//	q��ǰһ�뱣�����޸�keynum
}

//�����µĸ����T��ԭT��apΪ����ָ��
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

//��ӡ����ǰ���c�ĵ�i��λ�õ�key  
void print(BTNode c,int i)  
{  
    printf("(%d)\n",c.node[i].key);  
}  