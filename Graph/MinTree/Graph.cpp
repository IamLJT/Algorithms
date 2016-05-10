#include "Graph.h"
#include <stdio.h>

void CreateGraph(Graph *G)
{
	printf("������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	printf("������ͼ�Ķ�����Ϣ��\n");
	for(int i=0; i<G->NumVertex; i++)
	{
		fflush(stdin);	//	������뻺������Ϊ��ȷ����Ӱ��������������
		scanf("%c", &G->data[i]);	//	���붥����Ϣ
	}
	for(int i=0; i<G->NumVertex; i++)
		for(int j=0; j<G->NumVertex; j++)
		{
			if(i==j)
				G->Edge[i][j] = 0;
			else
				G->Edge[i][j] = INFINITY;	//	��ʼ��Ϊ����󣬼����ж���δ������
		}
	printf("������ߵ�������Ϣ(vi,vj)�ͱߵ�Ȩֵ��\n");
	for(int k=0; k<G->NumEdge; k++)
	{
		int i, j, w;
		fflush(stdin);
		scanf("%d%d%d", &i, &j, &w);
		G->Edge[i][j] = w;
		G->Edge[j][i] = w;	//	����ͼ
	}
}

void MiniSpanTree_Prim(Graph *G)
{
	int adjVex[MAXVEX];			//	��Ŷ�����±�ֵ
	EdgeType lowcost[MAXVEX];	//	�����С��Ȩֵ
	adjVex[0] = 0;				//	��ʼѡȡ�±�Ϊ0�Ķ���
	lowcost[0] = 0;				//	��ʾ�˶����ѱ������
	int sum = 0;					//	����������
	for(int i=1; i<G->NumVertex; i++)
	{
		lowcost[i] = G->Edge[0][i];	//	�����±�Ϊ0�Ķ��������ӵı�Ȩֵ����lowcost
		adjVex[i] = 0;			//	��ʼ��Ϊ0����һ��ʼ���Ǵ�0������
	}
	printf("����ķ�㷨��������ṹΪ��\n");
	for(int i=1; i<G->NumVertex; i++)
	{
		int min = INFINITY;		//	��ʼ����СֵΪ���޴�
		int k = 0;				//	���ڼ�¼Ȩֵ��С������±�
		for(int j=1; j<G->NumVertex; j++)
		{
			if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;			//	�ҳ�lowcost��0��Сֵ������һ���������ĵ㣬���������±�ֵ
			}
		}
		sum += min;
		lowcost[k] = 0;			//	�±�Ϊk�Ķ����Ѵ���
		printf("(%c, %c)\n", G->data[adjVex[k]], G->data[k]);
		for(int j=1; j<G->NumVertex; j++)
								//	�ҳ����Ѵ���ĵ��������СȨֵ
		{
			if(lowcost[j] != 0 && G->Edge[k][j] < lowcost[j])
								//	�����ǰ�Ķ����ȨֵС��֮ǰδ�������������Ķ���Ȩֵ
			{
				lowcost[j] = G->Edge[k][j];	//	����С��Ȩֵ����lowcost��Ӧ����λ��
				adjVex[j] = k;	//	��¼�´�ʱ��������СȨֵ�Ķ����±�
			}
		}
	}
	printf("������Ϊ��%d\n", sum);
}

void MiniSpanTree_Kruskal(Graph *G)
{
	Edge edge[MAXEDGE];		//	�������õı߼�
	int parent[MAXVEX];		//	�洢��ʹ�õĶ����±꣬��ֹ���ֻ�·
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
	printf("��³˹�����㷨���ɵ����ṹΪ��\n");
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
				break;			//	���Ѿ���n-1�����ˣ��Ͳ���Ҫ�ټ����Ƚ���
		}
	}
	printf("������Ϊ��%d\n", sum);
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