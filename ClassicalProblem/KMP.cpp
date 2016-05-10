#include <stdio.h>
#include <stdlib.h>

typedef char* String;

void get_next( String T, int *next)
{
	int j = 0, i = 1;
	next[1] = 0;

	while( i < T[0])
	{
		if( 0 == j || T[i] == T[j] )	//	KMP���ļ���
		{
			i++;
			j++;
			if(T[i] != T[j])
				next[i] = j;	
			else
				next[i] = next[j];
				//	������ͬԪ�أ�����Ҫ������εıȽ�
		}
		else
		{
			j = next[j];	//	����ͬʱ��ȥ������׺��ǰ׺��ʼ��ͬ�ĵط�
		}
	}
}

//	�����Ӵ� T ������ S �� pos ���ַ�֮���λ��
//	�������ڣ��򷵻�0
int Index_KMP( String S, String T, int pos)
{
	int i = pos;
	int j = 1;
	int next[255];

	get_next(T, next);
	printf("next����Ϊ��\n");
	for( int k = 1; k <= T[0]; k++)
		printf("%d ", next[k]);	//	��� next ����

	while( i <= S[0] && j <= T[0])
	{
		if( 0 == j || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];	//	������ģ��Ƚ�������ͬʱֻ��Ӹ�λ�ö�Ӧ��next����
							//	Ԫ��ָ��λ�ÿ�ʼ������������Ҫ�ظ��Ƚ��Ѿ��ȽϹ��ġ�
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
		printf("\nû�д��ַ�����\n");
	else
		printf("\n��ģʽ�ַ�����Ŀ���ַ����ĵ� %d ��λ�ã�\n", num);

	system("pause");
	return 0;
}