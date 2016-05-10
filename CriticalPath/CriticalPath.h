#ifndef _GRITICALPATH_H
#define _GRITICALPATH_H

#define MAXVEX 20

typedef int VertexType;		//	图的顶点数据类型

typedef struct edgenode
{
	int AdjVex;				//	顶点的下标值
	int weight;				//	顶点的权值
	struct edgenode* next;	//	指向下一个边集点
}EdgeNode;

typedef struct vertexnode
{
	VertexType data;		//	顶点信息
	int in;					//	顶点的入度
	EdgeNode *FirstEdge;	//	指向边集点
}VertexNode;

typedef struct graph
{
	VertexNode Vertex[MAXVEX];	//	图的顶点集
	int NumVertex, NumEdge;		//	图的顶点数和边数
}Graph;

void CreateGraph(Graph *G);		//	创建图
void TopoLogicalSort(Graph *G);	//	拓扑排序算法
void CriticalPath(Graph *G);	//	关键路径算法

#endif