/********�ڽӾ���д������ȱ���***************/

// ��Ȩֵ��
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 256

int flag[MAX_SIZE][MAX_SIZE], k = 0, ver[MAX_SIZE];

void picsearch(int (*v)[MAX_SIZE], int max, int row, int n)
{
	//int v0[MAX_SIZE][MAX_SIZE] = {0};
	int i, j;
	
	//for(i=0; i<max; i++)
	//	for(j=0; j<max; j++)
	//		v0[i][j] = v[i][j];

	for(i=0; i<max; i++)
	{
		if(i != n || n == row)	
		{
			flag[i][row] = 1;
		}
	}

	for(j=0; j<max; j++)
	{
		if(v[row][j] == 1 && flag[row][j] == 0)
		{
			printf("->%d", row);
			ver[k++] = j;
			picsearch(v, max, j, row);
		}
	} 
	
	printf("->%d", row);	//	���߹���·��ȫ�����Ƴ�����
							//	�����һ���������Ѿ��߹��ĵ㣬Ȼ��Ƚ�Ӧ�ÿ���
}

int main()
{
	int Vertex[MAX_SIZE][MAX_SIZE];
		//	Լ�����㰴0��ʼ����������
	int from, to, max = 0;
	while(scanf("%d,%d", &from, &to))
	{
		Vertex[from][to] = 1;
		Vertex[to][from] = 1;
		if(from > max)
			max = from;
		if(to > max)
			max = to;
	}
	max = max+1;
	for(int i=0; i<max; i++)
	{
		for(int j=0; j<max; j++)
		{
			printf("%d ", Vertex[i][j]);
		}
		printf("\n");
	}
			

	picsearch(Vertex, max, 0, 0);
	printf("\n");

	system("pause");
	return 0;
}

/*********************************************/