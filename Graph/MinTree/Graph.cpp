#include "Graph.h"
#include <stdio.h>

void CreateGraph(Graph *G)
{
	printf("请输入图的顶点数和边数：\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	printf("请输入图的顶点信息：\n");
	for(int i=0; i<G->NumVertex; i++)
	{
		fflush(stdin);	//	清空输入缓冲区，为了确保不影响后面的数据输入
		scanf("%c", &G->data[i]);	//	输入顶点信息
	}
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

void MiniSpanTree_Prim(Graph *G)
{
	int adjVex[MAXVEX];			//	存放顶点的下标值
	EdgeType lowcost[MAXVEX];	//	存放最小的权值
	adjVex[0] = 0;				//	初始选取下标为0的顶点
	lowcost[0] = 0;				//	表示此顶点已被处理过
	int sum = 0;					//	计算总消耗
	for(int i=1; i<G->NumVertex; i++)
	{
		lowcost[i] = G->Edge[0][i];	//	将与下标为0的顶点有连接的边权值存入lowcost
		adjVex[i] = 0;			//	初始化为0，即一开始都是从0出发的
	}
	printf("普里姆算法输出的树结构为：\n");
	for(int i=1; i<G->NumVertex; i++)
	{
		int min = INFINITY;		//	初始化最小值为无限大
		int k = 0;				//	用于记录权值最小顶点的下标
		for(int j=1; j<G->NumVertex; j++)
		{
			if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;			//	找出lowcost非0最小值，即下一个索引到的点，并保存其下标值
			}
		}
		sum += min;
		lowcost[k] = 0;			//	下标为k的顶点已处理
		printf("(%c, %c)\n", G->data[adjVex[k]], G->data[k]);
		for(int j=1; j<G->NumVertex; j++)
								//	找出从已处理的点出发的最小权值
		{
			if(lowcost[j] != 0 && G->Edge[k][j] < lowcost[j])
								//	如果当前的顶点的权值小于之前未被加入生成树的顶点权值
			{
				lowcost[j] = G->Edge[k][j];	//	将较小的权值放入lowcost对应顶点位置
				adjVex[j] = k;	//	记录下此时到顶点最小权值的顶点下标
			}
		}
	}
	printf("总消耗为：%d\n", sum);
}

void MiniSpanTree_Kruskal(Graph *G)
{
	Edge edge[MAXEDGE];		//	存放排序好的边集
	int parent[MAXVEX];		//	存储已使用的顶点下标，防止出现环路
	int n=0, m=0, k=0, sum=0;
	for(int i=0; i<MAXVEX; i++)
		parent[i] = 0;
	for(int i=0; i<G->NumVertex-1; i++)
		for(int j=i+1; j<G->NumVertex; j++)
		{
			if(G->Edge[i][j] < INFINITY)
			{
				edge[k].weight = G->Edge[i][j];
				edge[k].begin = i;
				edge[k].end = j;
				k++;
			}
		}
	sort(edge, G);
	k = 0;
	printf("克鲁斯卡尔算法生成的树结构为：\n");
	for(int i=0; i<G->NumEdge; i++)
	{
		n = Find(parent, edge[i].begin);
		m = Find(parent, edge[i].end);
		if(n != m)
		{
			parent[n] = m;
			printf("(%c, %c) %d\n", G->data[edge[i].begin], G->data[edge[i].end], edge[i].weight);
			k++;
			sum += edge[i].weight;
			if(G->NumVertex-1 == k)
				break;			//	当已经有n-1条边了，就不需要再继续比较了
		}
	}
	printf("总消耗为：%d\n", sum);
}

void sort(Edge *e, Graph *G)
{
	for(int i=0; i<G->NumEdge-1; i++)
		for(int j=i+1; j<G->NumEdge; j++)
		{
			if(e[j].weight < e[i].weight)
				swap(e, i, j);
		}
}

void swap(Edge *e, int i, int j)
{
	int temp;
	temp = e[i].begin;
	e[i].begin = e[j].begin;
	e[j].begin = temp;
	temp = e[i].end;
	e[i].end = e[j].end;
	e[j].end = temp;
	temp = e[i].weight;
	e[i].weight = e[j].weight;
	e[j].weight = temp;
}

int Find(int *parent, int f)
{
	while(parent[f] > 0)
		f = parent[f];
	return f;
}