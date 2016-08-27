#ifndef _GRAPH_H
#define _GRAPH_H

#define MAXVEX 10
#define MAXEDGE 10

typedef char VertexType;	//	顶点数据类型
typedef int EdgeType;		//	边表权值数据类型

typedef struct edge			//	边表结点
{
	int AdjEdge;			//	当前结点下标
	EdgeType weight;		//	边表结点权值
	struct edge* next;		//	边表指针域，指向下一个边表
}EdgeNode;

typedef struct vertexs
{
	VertexType data;		//	顶点数据
	EdgeNode* next;			//	顶点域，指向下一个边表
}VertexNode, vertex[MAXVEX];

typedef struct graph		//	图的邻接表
{
	vertex vertexes;		//	图的顶点
	int NumVertexes, NumEdges;	//	图的顶点数和边数
}Graph;

void CreateGraph(Graph *G);	//	建立图
void DFS(Graph *G, int i);	//	深度优先遍历
void DFSTraverse(Graph *G);	//	用邻接表深度优先遍历图
void BFSTraverse(Graph *G);	//	用邻接表广度优先遍历图

#endif