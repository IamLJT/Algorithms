#define MAX_TREE_SIZE	100

typedef char ElemType;

//	���ӽ��
typedef struct CTNODE
{
	int child;		//	���ӽ����±�
	struct CTNODE *next;	//	ָ����һ�������±�
}*ChildPtr;

//	��ͷ�ṹ
typedef struct
{
	ElemType data;	//	��������еĽ�������
	int parent;		//	���˫�׵��±�
	ChildPtr firstchild;	//	ָ���һ�����ӵ�ָ��
}CTBox;

//	���ṹ
typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];	//	�������
	int r, n;					//	���ͽ����
}