#ifndef _GRITICALPATH_H
#define _GRITICALPATH_H

#define MAXVEX 20

typedef int VertexType;		//	ͼ�Ķ�����������

typedef struct edgenode
{
	int AdjVex;				//	������±�ֵ
	int weight;				//	�����Ȩֵ
	struct edgenode* next;	//	ָ����һ���߼���
}EdgeNode;

typedef struct vertexnode
{
	VertexType data;		//	������Ϣ
	int in;					//	��������
	EdgeNode *FirstEdge;	//	ָ��߼���
}VertexNode;

typedef struct graph
{
	VertexNode Vertex[MAXVEX];	//	ͼ�Ķ��㼯
	int NumVertex, NumEdge;		//	ͼ�Ķ������ͱ���
}Graph;

void CreateGraph(Graph *G);		//	����ͼ
void TopoLogicalSort(Graph *G);	//	���������㷨
void CriticalPath(Graph *G);	//	�ؼ�·���㷨

#endif