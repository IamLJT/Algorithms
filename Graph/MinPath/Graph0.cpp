#include "Graph0.h"
#include <stdio.h>

void CreateGraph(Graph *G)
{
	printf("������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	//printf("������ͼ�Ķ�����Ϣ��\n");
	for(int i=0; i<G->NumVertex; i++)
		G->Vertex[i] = i;
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

void ShortestPath_Dijkstra(Graph *G, int v0, ShortPathTable *p, ShortWeight *d)
{
	int final[MAXVEX];		//	���final[w] == 1����ʾ����ô�v0��w�����·��
	int min;
	int k = 0;
	for(int i=0; i< MAXVEX; i++)
	{
		final[i] = 0;		//	��ʼ��v0�����ж�������·����δ�ҵ�
		(*p)[i] = 0;		//	��ʼ��·������Ϊ0
		(*d)[i] = G->Edge[v0][i];	//	����v0�ڽӵ�����·��Ȩֵ��ʼ����d
	}
	final[0] = 1;			//	v0��v0����Ҫ��·��
	(*d)[v0] = 0;			//	v0��v0��·��Ϊ0
	for(int i=1; i<G->NumVertex; i++)
	{
		min = INFINITY;
		for(int v=0; v<G->NumVertex; v++)
		{
			if(!final[v] && (*d)[v] < min)
			{
				min = (*d)[v];
				k = v;		//	�ӻ�δȷ��Ϊ���·���ĵ����ҵ���̵ĵ�
			}
		}
		final[k] = 1;
		for(int j=0; j<G->NumVertex; j++)	//	����d�����p����
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