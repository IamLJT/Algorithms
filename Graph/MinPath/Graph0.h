#pragma
#ifndef _GRAPH_H
#define _GRAPH_H

#define MAXVEX 20
#define MAXEDGE 20
#define INFINITY 65535

typedef struct graph
{
	int Vertex[MAXVEX];
	int Edge[MAXVEX][MAXVEX];
	int NumVertex, NumEdge;
}Graph;

typedef int ShortPathMatrix[MAXVEX][MAXVEX];
typedef int ShortPosition[MAXVEX][MAXVEX];

typedef int ShortPathTable[MAXVEX];	//	���ڴ洢���·��
typedef int ShortWeight[MAXVEX];	//	���ڴ洢���·����Ȩֵ

void CreateGraph(Graph *G);
void ShortestPath_Dijkstra(Graph *G, int v0, ShortPathTable *p, ShortWeight *d);
void ShortestPath_Floyd(Graph *G, ShortPosition *p, ShortPathMatrix *d);

#endif