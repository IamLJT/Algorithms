#include "CriticalPath.h"
#include <stdio.h>
#include <stdlib.h>

int *etv, *ltv;		//	事件最早发生和最迟发生时间数组
int top2;			//	用于Stack2的指针
int *Stack2;		//	用于存储拓扑序列的栈

void CreateGraph(Graph *G)
{
	EdgeNode *e = NULL;
	int from, to, w;
	printf("请输入顶点个数和边的个数：\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	for(int i=0; i<G->NumVertex; i++)
	{
		G->Vertex[i].data = i;
		G->Vertex[i].in = 0;
		G->Vertex[i].FirstEdge = NULL;
	}
	//	顶点的连接信息
	printf("请输入边的信息(vi, vj)和边的权值：\n");
	for(int i=0; i<G->NumEdge; i++)
	{
		scanf("%d%d%d", &from, &to, &w);
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->next = G->Vertex[from].FirstEdge;
		e->AdjVex = to;
		e->weight = w;
		G->Vertex[from].FirstEdge = e;
		++G->Vertex[e->AdjVex].in;
	}
}

void TopoLogicalSort(Graph *G)
{
	int *Stack;			//	用于存储入度为0的顶点下标
	int top = 0;		//	Stack栈的指针
	int count = 0;		//	统计输出的顶点数
	int gettop;			//	需要去除的顶点下标
	Stack = (int *)malloc(sizeof(int) * G->NumVertex);
	top = 0;
	Stack2 = (int *)malloc(sizeof(int) * G->NumVertex);
	for(int i=0; i<G->NumVertex; i++)
	{
		if(!(G->Vertex[i].in))		//	一开始将入度为0的顶点压入栈中
			Stack[++top] = i;
	}
	etv = (int *)malloc(sizeof(int) * G->NumVertex);
	for(int i=0; i<G->NumVertex; i++)
	{
		etv[i] = 0;		//	事件最早发生事件全部初始化为0
	}
	while(top != 0)		//	若Stack栈不为空，即还有未处理完的顶点
	{
		gettop = Stack[top--];	//	出栈
		count++;
		Stack2[++top2] = gettop;	//	将已处理的顶点压入栈Stack2
		for(EdgeNode *e = G->Vertex[gettop].FirstEdge; e ; e = e->next)
			//	处理gettop连接到的顶点
		{
			int k = e->AdjVex;
			if(!(--G->Vertex[k].in))
				Stack[++top] = k;
			if(etv[gettop] + e->weight > etv[k])
				etv[k] = etv[gettop] + e->weight;
		}
	}
	if(count < G->NumVertex)		//	如果顶点没有完全输出，说明有环，不是拓扑排列
	{
		printf("拓扑排序错误，程序即将推出：\n");
		system("pause");
		exit(1);
	}
}

void CriticalPath(Graph *G)
{
	int ete, lte;		//	声明事件最早发生时间和最迟发生时间的变量
	TopoLogicalSort(G);	//	拓扑排序求出事件的最早发生时间和拓扑序列Stack2
	ltv = (int*)malloc(sizeof(int) * G->NumVertex);
	for(int i=0; i<G->NumVertex; i++)
		ltv[i] = etv[G->NumVertex-1];
	while(top2 != 0)
	{
		int gettop = Stack2[top2--];	//	出栈
		for(EdgeNode *e = G->Vertex[gettop].FirstEdge; e; e=e->next)
		{
			int k = e->AdjVex;
			if(ltv[k] - e->weight < ltv[gettop])
				ltv[gettop] = ltv[k] - e->weight;
		}				//	计算每个事件的最晚发生事件
	}
	for(int i=0; i<G->NumVertex; i++)
	{
		for(EdgeNode *e = G->Vertex[i].FirstEdge; e; e=e->next)
		{
			int k = e->AdjVex;
			ete = etv[i];
			lte = ltv[k] - e->weight;
			if(ete == lte)		//	事件最早发生时间和最晚发生时间相等
			{
				printf("(V%d -> V%d) weight: %d\n", G->Vertex[i].data, G->Vertex[k].data, e->weight);
			}
		}
	}
}