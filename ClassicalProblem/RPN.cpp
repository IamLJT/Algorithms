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
	s->top = s->base;	//�ʼ��ջ������ջ��
	s->stackSize = STACK_INIT_SIZE;
}

#define STACKINCREMENT 10
void Push(sqStack *s, ElemType e)
{
	//���ջ����׷�ӿռ�
	if(s->top - s->base >= s->stackSize)
	{
		s->base = (ElemType *)realloc(
			s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
		if(!s->base)
			exit(0);

		s->top = s->base + s->stackSize;				//����ջ��
		s->stackSize = s->stackSize + STACKINCREMENT;	//����ջ���������
	}

	*(s->top) = e;
	s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
	if(s->top == s->base)
		return;
	*e = *--(s->top);	//����ɾ���ѳ�ջ�Ŀռ�
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

	printf("�밴�沨�����ʽ�������������"
		"�������������֮���ÿո����:\n");
	scanf("%c",&c);
	
	while(c!='#')
	{
		while( isdigit(c) || c == '.')	//���ڹ�������
		{
			str[i++] = c;
			str[i] = '\0';
			if(i >= 10)
			{
				printf("��������ĵ������ݹ���\n");
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
				printf("\n���ִ���\n");
				return -1;
			}
			break;
		}
		scanf("%c", &c);
	}

	Pop(&s, &d);
	printf("\n���յļ�����Ϊ��%.2f\n", d);

	system("pause");
	return 0;
}