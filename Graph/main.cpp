#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Graph G;
	CreateGraph(&G);
	printf("������ȱ�����\n");
	DFSTraverse(&G);
	printf("\n������ȱ�����\n");
	BFSTraverse(&G);
	printf("\n");

	system("pause");
	return 0;
}