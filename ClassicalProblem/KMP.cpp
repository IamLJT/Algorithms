#include <stdio.h>
#include <stdlib.h>

typedef char* String;

void get_next( String T, int *next)
{
	int j = 0, i = 1;
	next[1] = 0;

	while( i < T[0])
	{
		if( 0 == j || T[i] == T[j] )	//	KMP核心计算
		{
			i++;
			j++;
			if(T[i] != T[j])
				next[i] = j;	
			else
				next[i] = next[j];
				//	对于相同元素，不需要经过多次的比较
		}
		else
		{
			j = next[j];	//	不相同时则去索引后缀和前缀开始相同的地方
		}
	}
}

//	返回子串 T 在主串 S 第 pos 个字符之后的位置
//	若不存在，则返回0
int Index_KMP( String S, String T, int pos)
{
	int i = pos;
	int j = 1;
	int next[255];

	get_next(T, next);
	printf("next数组为：\n");
	for( int k = 1; k <= T[0]; k++)
		printf("%d ", next[k]);	//	输出 next 数组

	while( i <= S[0] && j <= T[0])
	{
		if( 0 == j || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];	//	计算核心：比较遇到不同时只需从该位置对应的next数组
							//	元素指定位置开始索引，而不需要重复比较已经比较过的。
		}
	}

	if( j > T[0] )
	{
		return i - T[0];
	}
	else
	{
		return 0;
	}
}

int main()
{
	char str[255] = " abaababaabaaaaabababaa";
	char T[255] = " aaaaaba";

	str[0] = 23;
	T[0] = 7;

	int next[255];

	int num = Index_KMP(str, T, 1);

	if(num == 0)
		printf("\n没有此字符串！\n");
	else
		printf("\n改模式字符串在目标字符串的第 %d 个位置！\n", num);

	system("pause");
	return 0;
}