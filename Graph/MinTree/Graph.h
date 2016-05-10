#ifndef _GRAPH_H
#define _GRAPH_H

#define MAXVEX 20
#define MAXEDGE 20
#define INFINITY 65535	//	表示没有相交的边

typedef char VertexType;	//	顶点数据类型
typedef int EdgeType;		//	边表权值类型

typedef struct graph
{
	VertexType data[MAXVEX];	//	图的顶点
	EdgeType Edge[MAXVEX][MAXVEX];	//	图的边表
	int NumVertex, NumEdge;		//	图的顶点数与边数
}Graph;

typedef struct edge
{
	int begin;
	int end;
	int weight;
}Edge;

void CreateGraph(Graph *G);			//	创建图

int Find(int *parent, int f);
void sort(Edge *e, Graph *G);		//	对有权值的边进行排序
void swap(Edge *e, int i, int j);
void MiniSpanTree_Kruskal(Graph *G);//	最小生成树克鲁斯卡尔算法
void MiniSpanTree_Prim(Graph *G);	//	最小生成树普里姆算法


#endif