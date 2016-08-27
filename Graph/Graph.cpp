#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool visited[MAXVEX];	//	����ѷ���

void CreateGraph(Graph *G)
{
	EdgeNode *e = NULL;
	printf("������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &G->NumVertexes, &G->NumEdges);
	printf("������ͼ�Ķ�����Ϣ��\n");
	for(int i=0; i<G->NumVertexes; i++)
	{
		fflush(stdin);
		scanf("%c", &G->vertexes[i].data);
		G->vertexes[i].next = NULL;
	}
	for(int k=0; k<G->NumEdges; k++)
	{
		printf("������ͼ�ıߵ�������Ϣ(vi,vj)��Ȩֵ��\n");
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
		//	����������ͼ���Դ��ڷ�������
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		if(!e)
			exit(OVERFLOW);
		e->AdjEdge = i;
		e->weight = w;
		e->next = G->vertexes[j].next;
		G->vertexes[j].next = e;
	}
}

void DFS(Graph *G, int i)		//	������ȱ���
{
	visited[i] = true;			//	�����±�ΪI�Ķ����ѱ�����
	printf("%c ", G->vertexes[i].data);	//	���������Ϣ
	EdgeNode* p = G->vertexes[i].next;	//	��һ���߱���
	while(p)
	{
		if(!visited[p->AdjEdge])	//	���δ��������ݹ�
			DFS(G, p->AdjEdge);
		p = p->next;
	}
}

void DFSTraverse(Graph *G)
{
	for(int i=0; i<G->NumVertexes; i++)
		visited[i] = false;		//	��ʼ��ÿ����㶼δ������
	for(int i=0; i<G->NumVertexes; i++)
		if(!visited[i])
			DFS(G, i);			//	ѡȡһ��δ�����ʵĽ������������
								//	�������ͨͼ��ִֻ��һ�Σ�visited����ʱȫ�ֱ���
}

void BFSTraverse(Graph *G)
{
	Queue q;
	InitQueue(&q);	//	��ʼ������
	for(int i=0; i<G->NumVertexes; i++)
		visited[i] = false;		//	��ʼ�����н��δ������
	for(int i=0; i<G->NumVertexes; i++)
	{
		if(!visited[i])			//	ѡȡһ��δ�����ʹ��Ķ���
		{
			visited[i] = true;
			printf("%c ", G->vertexes[i].data);
			EnQueue(&q, i);		//	��ǰ������±����
			while(!IsEmpty(&q))
			{
				DeQueue(&q, &i);//	����
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