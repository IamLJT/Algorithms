#include "Graph0.h"
#include <stdio.h>

void CreateGraph(Graph *G)
{
	printf("请输入图的顶点数和边数：\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	//printf("请输入图的顶点信息：\n");
	for(int i=0; i<G->NumVertex; i++)
		G->Vertex[i] = i;
	for(int i=0; i<G->NumVertex; i++)
		for(int j=0; j<G->NumVertex; j++)
		{
			if(i==j)
				G->Edge[i][j] = 0;
			else
				G->Edge[i][j] = INFINITY;	//	初始化为无穷大，即所有顶点未有连接
		}
	printf("请输入边的连接信息(vi,vj)和边的权值：\n");
	for(int k=0; k<G->NumEdge; k++)
	{
		int i, j, w;
		fflush(stdin);
		scanf("%d%d%d", &i, &j, &w);
		G->Edge[i][j] = w;
		G->Edge[j][i] = w;	//	无向图
	}
}

void ShortestPath_Dijkstra(Graph *G, int v0, ShortPathTable *p, ShortWeight *d)
{
	int final[MAXVEX];		//	如果final[w] == 1，表示已求得从v0到w的最短路径
	int min;
	int k = 0;
	for(int i=0; i< MAXVEX; i++)
	{
		final[i] = 0;		//	初始化v0到所有顶点的最短路径都未找到
		(*p)[i] = 0;		//	初始化路径数组为0
		(*d)[i] = G->Edge[v0][i];	//	将与v0邻接的所有路径权值初始化给d
	}
	final[0] = 1;			//	v0到v0不需要求路径
	(*d)[v0] = 0;			//	v0到v0的路径为0
	for(int i=1; i<G->NumVertex; i++)
	{
		min = INFINITY;
		for(int v=0; v<G->NumVertex; v++)
		{
			if(!final[v] && (*d)[v] < min)
			{
				min = (*d)[v];
				k = v;		//	从还未确认为最短路径的点中找到最短的点
			}
		}
		final[k] = 1;
		for(int j=0; j<G->NumVertex; j++)	//	修正d数组和p数组
		{
			if(!final[j] && min+G->Edge[k][j]<(*d)[j])
			{
				(*d)[j] = min + G->Edge[k][j];
				(*p)[j] = k;
			}
		}
	}
}

void ShortestPath_Floyd(Graph *G, ShortPosition *p, ShortPathMatrix *d)
{
	for(int i=0; i<G->NumVertex; i++)
		for(int j=0; j<G->NumVertex; j++)
		{
			(*p)[i][j] = j;
			(*d)[i][j] = G->Edge[i][j];
		}
	for(int k=0; k<G->NumVertex; k++)
	{
		for(int i=0; i<G->NumVertex; i++)
		{
			for(int j=0; j<G->NumVertex; j++)
			{
				if((*d)[i][j] > (*d)[i][k] + (*d)[k][j])
				{
					(*d)[i][j] = (*d)[i][k] + (*d)[k][j];
					(*p)[i][j] = (*p)[i][k];
				}
			}
		}
	}
}