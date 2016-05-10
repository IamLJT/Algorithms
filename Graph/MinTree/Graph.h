#ifndef _GRAPH_H
#define _GRAPH_H

#define MAXVEX 20
#define MAXEDGE 20
#define INFINITY 65535	//	��ʾû���ཻ�ı�

typedef char VertexType;	//	������������
typedef int EdgeType;		//	�߱�Ȩֵ����

typedef struct graph
{
	VertexType data[MAXVEX];	//	ͼ�Ķ���
	EdgeType Edge[MAXVEX][MAXVEX];	//	ͼ�ı߱�
	int NumVertex, NumEdge;		//	ͼ�Ķ����������
}Graph;

typedef struct edge
{
	int begin;
	int end;
	int weight;
}Edge;

void CreateGraph(Graph *G);			//	����ͼ

int Find(int *parent, int f);
void sort(Edge *e, Graph *G);		//	����Ȩֵ�ı߽�������
void swap(Edge *e, int i, int j);
void MiniSpanTree_Kruskal(Graph *G);//	��С��������³˹�����㷨
void MiniSpanTree_Prim(Graph *G);	//	��С����������ķ�㷨


#endif