#include <iostream>
using namespace std;

int main()
{
	int n=0;
	double min_s=0, hour_s=0.0;
	double epi = 6.0/120;
	while(n < (11*60+30)*60)
	{
		if(abs(min_s-hour_s)<epi)
			printf("%d\n", n);
		min_s += 6.0/60;
		if(min_s>360)
			min_s = min_s-360;
		hour_s += 1.0/120;
		n++;
	}
	system("pause");
	return 0;
}