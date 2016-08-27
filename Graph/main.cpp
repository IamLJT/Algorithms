#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Graph G;
	CreateGraph(&G);
	printf("深度优先遍历：\n");
	DFSTraverse(&G);
	printf("\n广度优先遍历：\n");
	BFSTraverse(&G);
	printf("\n");

	system("pause");
	return 0;
}