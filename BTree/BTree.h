#ifndef _BTREE_H
#define _BTREE_H

#define M 3			//	B���Ľף�����Ϊ3
#define N 17		//	����Ԫ�صĸ���

typedef struct BTNode
{
	int keynum;		//	����йؼ��ֵĸ����������Ĵ�С
	struct BTNode *parent;	//	ָ��˫�׽��
	struct Node		//	�ؼ�������
	{
		int key;	//	����еĹؼ���
		struct BTNode *ptr;	//	����ָ������
		int recptr;	//	��¼ָ������
	}node[M + 1];	//	key��recptr��0�ŵ�Ԫδ��
}BTNode, *BTree;	//	B������B������

typedef struct
{
	BTNode *pt;		//	ָ���ҵ��Ľ��
	int i;			//	1......m�������ҵ��Ľ���йؼ������
	int tag;		//	1��:���ҳɹ���0������ʧ��
}Result;			//	B���Ĳ��ҽ������

//��p->node[1]......p->node[keynum]�в���k������λ��p->node[i].key
//<= k < p->node[i+1].key
int Search(BTree p, int k);

//��M��B��T�ϲ��ҹؼ���K�����ؽ��Result
//���ҳɹ���tag=1��ptָ������ؼ���k�Ľ�㣬iΪK�ڽ���λ��
//����ʧ�ܣ�tag=0��ptָ��KӦ����Ľ�㣬i...i+1֮�����K
Result SearchBTree(BTree T, int k);

//��key���뵽*qָ��Ľ��ĵ�i+1��λ��
void Insert(BTree *q, int i, int key, BTree ap);

//��M��B��T�ϣ���q��ָ��Ľ���i��i+1���м����key
//������Ľڵ��������˫�������б�Ҫ�Ľ����ѵ�����ʹT��Ȼ��m��B��
void InsertBTree(BTree *T, int key, BTree q, int i);

//�����q���ѳ�������㣬ǰһ�뱣������һ�������������ap
void Split(BTree *q, BTree *ap);

//�����µĸ����T��ԭT��apΪ����ָ��
void NewRoot(BTree *T, int key, BTree ap);

//��ӡ����ǰ���c�ĵ�i��λ�õ�key
void print(BTNode c, int i);

#endif