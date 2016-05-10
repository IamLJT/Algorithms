#ifndef _BISEARCHTREE_H
#define _BISEARCHTREE_H

typedef int Element;

typedef struct Node
{
	Element data;
	struct Node* Left;
	struct Node* Right;
}SearchNode, *SearchTree, *Position;

void MakeEmpty(SearchTree T);
bool IsEmpty(SearchTree T);
bool Find(Element x, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
Position Insert(Element x, SearchTree &T);
Position Delete(Element x, SearchTree &T);
void InOrderTraverse(SearchTree T);

#endif