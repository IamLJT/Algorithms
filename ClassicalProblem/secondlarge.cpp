#include <iostream>
#include <vector>
using namespace std;

int max0(int n1, int n2)
{
	return n1>n2?n1:n2;
}

int min0(int n1, int n2)
{
	return n1<n2?n1:n2;
}

int merge(vector<int> num, int p, int q, int& fl, int& sl)
{
	if(p==q)
		return num[p];
	int mid=(p+q)/2;
	int n1=merge(num, p, mid, fl, sl);
	int n2=merge(num, mid+1, q, fl, sl);
	sl=max0(min0(fl, max0(n1, n2))==fl?0:min0(fl, max0(n1, n2)), max0(sl, min0(n1, n2)));
	fl=max0(fl, max0(n1,n2));
	
	return max0(n1, n2);
}

int secondlarge(vector<int> num)
{
	if(num.size()<=1) return -1;
	if(num.size()==2) return min0(num[0], num[1]);
	int fl=max0(num[0], num[1]), sl=min0(num[0], num[1]);
	int res=merge(num, 2, num.size()-1, fl, sl);
	return sl;
}

int main()
{
	int num[]={1,3,5,2,4,9,11,4,5,6};
	vector<int> nums(num, num+sizeof(num)/sizeof(int));
	cout << secondlarge(nums) << endl;
	system("pause");
	return 0;
}