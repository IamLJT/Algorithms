#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define ERROR	0
#define OK		1
#define MAXBUFFER 10

typedef double ElemType;

typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

#define STACK_INIT_SIZE 100
void InitStack(sqStack *s)
{
	s->base = (ElemType *)malloc(
		STACK_INIT_SIZE * sizeof(ElemType));
	if( !s->base )
		exit(0);
	s->top = s->base;	//最开始，栈顶就是栈底
	s->stackSize = STACK_INIT_SIZE;
}

#define STACKINCREMENT 10
void Push(sqStack *s, ElemType e)
{
	//如果栈满，追加空间
	if(s->top - s->base >= s->stackSize)
	{
		s->base = (ElemType *)realloc(
			s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
		if(!s->base)
			exit(0);

		s->top = s->base + s->stackSize;				//设置栈顶
		s->stackSize = s->stackSize + STACKINCREMENT;	//设置栈的最大容量
	}

	*(s->top) = e;
	s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
	if(s->top == s->base)
		return;
	*e = *--(s->top);	//无需删除已出栈的空间
}

void ClearStack(sqStack *s)
{
	s->top = s->base;
}

void DestroyStack(sqStack *s)
{
	int i, len;
	len = s->stackSize;
	for(i=0; i<len; i++)
	{
		free(s->base);
		s->base++;
	}
	s->base = s->top = NULL;
	s->stackSize = 0;
}

int StackLen(sqStack *s)
{
	return (s->top - s->base);
}

bool StackEmpty(sqStack *s)
{
	if(s->top == s->base)
		return false;
	else
		return true;
}

int main()
{
	char c;
	sqStack s;
	double d, e;
	char str[MAXBUFFER];
	int i=0;

	InitStack(&s);

	printf("请按逆波兰表达式输入带计算数据"
		"，数据与运算符之间用空格隔开:\n");
	scanf("%c",&c);
	
	while(c!='#')
	{
		while( isdigit(c) || c == '.')	//用于过滤数字
		{
			str[i++] = c;
			str[i] = '\0';
			if(i >= 10)
			{
				printf("出错：输入的单个数据过大！\n");
				return -1;
			}
			scanf("%c", &c);
			if( c == ' ' )
			{
				d = atof(str);
				Push(&s, d);
				i = 0;
				break;
			}
		}

		switch(c)
		{
		case '+':
			Pop(&s, &e);
			Pop(&s, &d);
			Push(&s, d+e);
			break;
		case '-':
			Pop(&s, &e);
			Pop(&s, &d);
			Push(&s, d-e);
			break;
		case '*':
			Pop(&s, &e);
			Pop(&s, &d);
			Push(&s, d*e);
			break;
		case '/':
			Pop(&s, &e);
			Pop(&s, &d);
			if(e != 0)
				Push(&s, d/e);
			else
			{
				printf("\n出现错误！\n");
				return -1;
			}
			break;
		}
		scanf("%c", &c);
	}

	Pop(&s, &d);
	printf("\n最终的计算结果为：%.2f\n", d);

	system("pause");
	return 0;
}