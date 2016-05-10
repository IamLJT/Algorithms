#include "CriticalPath.h"
#include <stdio.h>
#include <stdlib.h>

int *etv, *ltv;		//	�¼����緢������ٷ���ʱ������
int top2;			//	����Stack2��ָ��
int *Stack2;		//	���ڴ洢�������е�ջ

void CreateGraph(Graph *G)
{
	EdgeNode *e = NULL;
	int from, to, w;
	printf("�����붥������ͱߵĸ�����\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	for(int i=0; i<G->NumVertex; i++)
	{
		G->Vertex[i].data = i;
		G->Vertex[i].in = 0;
		G->Vertex[i].FirstEdge = NULL;
	}
	//	�����������Ϣ
	printf("������ߵ���Ϣ(vi, vj)�ͱߵ�Ȩֵ��\n");
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
	int *Stack;			//	���ڴ洢���Ϊ0�Ķ����±�
	int top = 0;		//	Stackջ��ָ��
	int count = 0;		//	ͳ������Ķ�����
	int gettop;			//	��Ҫȥ���Ķ����±�
	Stack = (int *)malloc(sizeof(int) * G->NumVertex);
	top = 0;
	Stack2 = (int *)malloc(sizeof(int) * G->NumVertex);
	for(int i=0; i<G->NumVertex; i++)
	{
		if(!(G->Vertex[i].in))		//	һ��ʼ�����Ϊ0�Ķ���ѹ��ջ��
			Stack[++top] = i;
	}
	etv = (int *)malloc(sizeof(int) * G->NumVertex);
	for(int i=0; i<G->NumVertex; i++)
	{
		etv[i] = 0;		//	�¼����緢���¼�ȫ����ʼ��Ϊ0
	}
	while(top != 0)		//	��Stackջ��Ϊ�գ�������δ������Ķ���
	{
		gettop = Stack[top--];	//	��ջ
		count++;
		Stack2[++top2] = gettop;	//	���Ѵ���Ķ���ѹ��ջStack2
		for(EdgeNode *e = G->Vertex[gettop].FirstEdge; e ; e = e->next)
			//	����gettop���ӵ��Ķ���
		{
			int k = e->AdjVex;
			if(!(--G->Vertex[k].in))
				Stack[++top] = k;
			if(etv[gettop] + e->weight > etv[k])
				etv[k] = etv[gettop] + e->weight;
		}
	}
	if(count < G->NumVertex)		//	�������û����ȫ�����˵���л���������������
	{
		printf("����������󣬳��򼴽��Ƴ���\n");
		system("pause");
		exit(1);
	}
}

void CriticalPath(Graph *G)
{
	int ete, lte;		//	�����¼����緢��ʱ�����ٷ���ʱ��ı���
	TopoLogicalSort(G);	//	������������¼������緢��ʱ�����������Stack2
	ltv = (int*)malloc(sizeof(int) * G->NumVertex);
	for(int i=0; i<G->NumVertex; i++)
		ltv[i] = etv[G->NumVertex-1];
	while(top2 != 0)
	{
		int gettop = Stack2[top2--];	//	��ջ
		for(EdgeNode *e = G->Vertex[gettop].FirstEdge; e; e=e->next)
		{
			int k = e->AdjVex;
			if(ltv[k] - e->weight < ltv[gettop])
				ltv[gettop] = ltv[k] - e->weight;
		}				//	����ÿ���¼����������¼�
	}
	for(int i=0; i<G->NumVertex; i++)
	{
		for(EdgeNode *e = G->Vertex[i].FirstEdge; e; e=e->next)
		{
			int k = e->AdjVex;
			ete = etv[i];
			lte = ltv[k] - e->weight;
			if(ete == lte)		//	�¼����緢��ʱ���������ʱ�����
			{
				printf("(V%d -> V%d) weight: %d\n", G->Vertex[i].data, G->Vertex[k].data, e->weight);
			}
		}
	}
}