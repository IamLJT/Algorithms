#ifndef _GRAPH_H
#define _GRAPH_H

#define MAXVEX 10
#define MAXEDGE 10

typedef char VertexType;	//	������������
typedef int EdgeType;		//	�߱�Ȩֵ��������

typedef struct edge			//	�߱���
{
	int AdjEdge;			//	��ǰ����±�
	EdgeType weight;		//	�߱���Ȩֵ
	struct edge* next;		//	�߱�ָ����ָ����һ���߱�
}EdgeNode;

typedef struct vertexs
{
	VertexType data;		//	��������
	EdgeNode* next;			//	������ָ����һ���߱�
}VertexNode, vertex[MAXVEX];

typedef struct graph		//	ͼ���ڽӱ�
{
	vertex vertexes;		//	ͼ�Ķ���
	int NumVertexes, NumEdges;	//	ͼ�Ķ������ͱ���
}Graph;

void CreateGraph(Graph *G);	//	����ͼ
void DFS(Graph *G, int i);	//	������ȱ���
void DFSTraverse(Graph *G);	//	���ڽӱ�������ȱ���ͼ
void BFSTraverse(Graph *G);	//	���ڽӱ������ȱ���ͼ

#endif