#include <stdio.h>
#include <stdlib.h>

int num = 0;

// 将 n 个盘子从 x 借助 y 移动到 z
int move(int n, char x, char y, char z)
{
	if (1 == n)
	{
		printf("%c%d-->%c\n", x, n, z);
		num++;
	}
	else
	{
		move(n-1, x, z, y);	//将 n-1 个盘子从 x 借助 z 移动到 y 
		printf("%c%d-->%c\n", x, n, z);//将第 n 个盘子从 x 移动到 z
		num++;
		move(n-1, y, x, z);	//将 n-1 个盘子从 y 借助 x 移动到 z
	}
	return num;
}

int main()
{
	int n, sum=0;
	
	printf("请输入汉诺塔的层数：");
	while(scanf("%d", &n))
	{
		printf("移动的步骤如下：\n");
		sum = move(n, 'X', 'Y', 'Z');
		printf("总步数为：%d", sum);
		num = 0;
		printf("\n请输入汉诺塔的层数：");
	}
	system("pause");
	return 0;
}