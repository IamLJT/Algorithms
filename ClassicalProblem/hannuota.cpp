#include <stdio.h>
#include <stdlib.h>

int num = 0;

// �� n �����Ӵ� x ���� y �ƶ��� z
int move(int n, char x, char y, char z)
{
	if (1 == n)
	{
		printf("%c%d-->%c\n", x, n, z);
		num++;
	}
	else
	{
		move(n-1, x, z, y);	//�� n-1 �����Ӵ� x ���� z �ƶ��� y 
		printf("%c%d-->%c\n", x, n, z);//���� n �����Ӵ� x �ƶ��� z
		num++;
		move(n-1, y, x, z);	//�� n-1 �����Ӵ� y ���� x �ƶ��� z
	}
	return num;
}

int main()
{
	int n, sum=0;
	
	printf("�����뺺ŵ���Ĳ�����");
	while(scanf("%d", &n))
	{
		printf("�ƶ��Ĳ������£�\n");
		sum = move(n, 'X', 'Y', 'Z');
		printf("�ܲ���Ϊ��%d", sum);
		num = 0;
		printf("\n�����뺺ŵ���Ĳ�����");
	}
	system("pause");
	return 0;
}