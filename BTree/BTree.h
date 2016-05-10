#ifndef _BTREE_H
#define _BTREE_H

#define M 3			//	B树的阶，暂设为3
#define N 17		//	数据元素的个数

typedef struct BTNode
{
	int keynum;		//	结点中关键字的个数，即结点的大小
	struct BTNode *parent;	//	指向双亲结点
	struct Node		//	关键字向量
	{
		int key;	//	结点中的关键字
		struct BTNode *ptr;	//	子树指针向量
		int recptr;	//	记录指针向量
	}node[M + 1];	//	key，recptr的0号单元未用
}BTNode, *BTree;	//	B树结点和B树类型

typedef struct
{
	BTNode *pt;		//	指向找到的结点
	int i;			//	1......m，在所找到的结点中关键字序号
	int tag;		//	1：:查找成功，0：查找失败
}Result;			//	B树的查找结果类型

//在p->node[1]......p->node[keynum]中查找k所处的位置p->node[i].key
//<= k < p->node[i+1].key
int Search(BTree p, int k);

//在M阶B树T上查找关键字K，返回结果Result
//查找成功，tag=1，pt指向包含关键字k的结点，i为K在结点的位置
//查找失败，tag=0，pt指向K应插入的结点，i...i+1之间插入K
Result SearchBTree(BTree T, int k);

//将key插入到*q指向的结点的第i+1个位置
void Insert(BTree *q, int i, int key, BTree ap);

//在M阶B树T上，在q所指向的结点第i与i+1的中间插入key
//若引起的节点过大，则沿双亲链进行必要的结点分裂调整，使T依然是m阶B树
void InsertBTree(BTree *T, int key, BTree q, int i);

//将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
void Split(BTree *q, BTree *ap);

//生成新的根结点T，原T和ap为子树指针
void NewRoot(BTree *T, int key, BTree ap);

//打印出当前结点c的第i个位置的key
void print(BTNode c, int i);

#endif