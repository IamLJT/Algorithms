#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************/
typedef char Elemtype;

//	建立队列，用来存储赫夫曼树的元素
typedef struct HuffmanNode
{
	Elemtype data;
	int value;
	struct HuffmanNode *next;
}HuffmanNode, *HuffmanPtr;

typedef struct
{
	HuffmanPtr front, rear;
}LinkHuff;

void initHuff(LinkHuff *q)
{
	q->front = q->rear = (HuffmanPtr)malloc(sizeof(HuffmanNode));
	if( !q->front )
		exit(0);
	q->front->next = NULL;
}

//	入队列
void InsertHuff(LinkHuff *q, Elemtype e, int v)
{
	HuffmanPtr p;
	p = (HuffmanPtr)malloc(sizeof(HuffmanNode));
	if( p == NULL )
		exit(0);
	p->data = e;
	p->value = v;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}

void Orderinsert(LinkHuff *q, Elemtype e, int v)
{
	HuffmanPtr temp, p;
	p = (HuffmanPtr)malloc(sizeof(HuffmanNode));
	p->data = e;
	p->value = v;
	temp = q->front;
	while((temp->next != NULL) && 
		(p->value > temp->next->value))
	{
		temp = temp->next;
	}
	p->next = temp->next;
	temp->next = p;
	if(q->rear->next != NULL)
		q->rear = q->rear->next;
}

//	出队列
void DeleteHuff(LinkHuff *q, Elemtype *e, int *c)
{
	HuffmanPtr p;
	if( q->front == q->rear )
		return;
	p = q->front->next;
	*e = p->data;
	*c = p->value;
	q->front->next = p->next;
	if(q->rear == p)
		q->rear = q->front;
	free(p);
}

/****************************************************/
//	线索存储标志位
//	Link(0)：表示指向左右孩子的指针
//	Thread(1)：表示指向前驱后继的线索
typedef enum {Link, Thread} PointerTag;

//	二叉树的建立
typedef struct BiTNode
{
	Elemtype data;
	int value;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/***************************************************/

#define MAXSIZE 256

int num[MAXSIZE];
char stringABC[MAXSIZE];

void strnum(char str[])	// 计算每个字母的次数并存到队列
{
	int i, j, count, flag = 0, k = 0;
	for(i=0; i<strlen(str); i++)
	{
		count = 0;
		for(j=0; j<i; j++)
		{
			flag = 0;
			if(str[j] == str[i])
			{
				flag = 1;
				break;
			}//之前没有出现过的字符才去比较
		}
		if(1 == flag)
			continue;
		for(j=i; j<strlen(str); j++)
		{
			if(str[j] == str[i])
				count++;
		}
		num[k]=count;
		stringABC[k] = str[i];
		k++;
	}
	stringABC[k] = '\0';
}

//	给输出排序后压入到队列中
void order(LinkHuff *p)
{
	int temp = 0;
	char tempstr;
	
	for(int i=0; i<strlen(stringABC); i++)
	{
		temp = num[i];
		tempstr = stringABC[i];
		for(int j=i; j<strlen(stringABC); j++)
		{
			if(temp > num[j])
			{
				num[i] = num[j];
				num[j] = temp;
				temp = num[i];
				stringABC[i] = stringABC[j];
				stringABC[j] = tempstr;
				tempstr = stringABC[i];
			}
		}
		InsertHuff(p, tempstr, temp);
	}
}

int main()
{
	char str[MAXSIZE], c1, c2, c;
	int v1, v2, v;
	printf("请输入字符串：\n");
	scanf("%s", str);
	strnum(str);

	LinkHuff p;
	initHuff(&p);
	order(&p);

	/*q->data = 'z';
	q->value = 5;

	Orderinsert(&p, q);*/

	while(p.front != p.rear)
	{
		DeleteHuff(&p, &c1, &v1);
		if(p.front != p.rear)
			DeleteHuff(&p, &c2, &v2);
		else
			break;
		c = ' ';
		v = v1 + v2;
		Orderinsert(&p, c, v);	//将前两个数相加后再排到原队列去
	}
	printf("%d\n", v1);

	system("pause");
	return 0;
}