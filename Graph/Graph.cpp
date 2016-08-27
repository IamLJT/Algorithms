#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool visited[MAXVEX];	//	标记已访问

void CreateGraph(Graph *G)
{
	EdgeNode *e = NULL;
	printf("请输入图的顶点数和边数：\n");
	scanf("%d%d", &G->NumVertexes, &G->NumEdges);
	printf("请输入图的顶点信息：\n");
	for(int i=0; i<G->NumVertexes; i++)
	{
		fflush(stdin);
		scanf("%c", &G->vertexes[i].data);
		G->vertexes[i].next = NULL;
	}
	for(int k=0; k<G->NumEdges; k++)
	{
		printf("请输入图的边的连接信息(vi,vj)及权值：\n");
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		if(!e)
			exit(OVERFLOW);
		fflush(stdin);
		int i, j, w;
		scanf("%d%d%d", &i, &j, &w);
		e->AdjEdge = j;
		e->weight = w;
		e->next = G->vertexes[i].next;
		G->vertexes[i].next = e;
		//	由于是无向图所以存在反链现象
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		if(!e)
			exit(OVERFLOW);
		e->AdjEdge = i;
		e->weight = w;
		e->next = G->vertexes[j].next;
		G->vertexes[j].next = e;
	}
}

void DFS(Graph *G, int i)		//	深度优先遍历
{
	visited[i] = true;			//	设置下标为I的顶点已被访问
	printf("%c ", G->vertexes[i].data);	//	输出顶点信息
	EdgeNode* p = G->vertexes[i].next;	//	下一个边表结点
	while(p)
	{
		if(!visited[p->AdjEdge])	//	如果未被访问则递归
			DFS(G, p->AdjEdge);
		p = p->next;
	}
}

void DFSTraverse(Graph *G)
{
	for(int i=0; i<G->NumVertexes; i++)
		visited[i] = false;		//	初始化每个结点都未被访问
	for(int i=0; i<G->NumVertexes; i++)
		if(!visited[i])
			DFS(G, i);			//	选取一个未被访问的结点进行深度优先
								//	如果是连通图，只执行一次，visited数组时全局变量
}

void BFSTraverse(Graph *G)
{
	Queue q;
	InitQueue(&q);	//	初始化队列
	for(int i=0; i<G->NumVertexes; i++)
		visited[i] = false;		//	初始化所有结点未被访问
	for(int i=0; i<G->NumVertexes; i++)
	{
		if(!visited[i])			//	选取一个未被访问过的顶点
		{
			visited[i] = true;
			printf("%c ", G->vertexes[i].data);
			EnQueue(&q, i);		//	当前顶点的下标入队
			while(!IsEmpty(&q))
			{
				DeQueue(&q, &i);//	出队
				EdgeNode* p = G->vertexes[i].next;
				while(p)
				{
					if(!visited[p->AdjEdge])
					{
						visited[p->AdjEdge] = true;
						printf("%c ", G->vertexes[p->AdjEdge].data);
						EnQueue(&q, p->AdjEdge);
					}
					p = p->next;
				}
			}
		}
	}
}