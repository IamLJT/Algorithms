/*

*/
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

vector<int> primenumber(int n)
{
	vector<int> res;
	if(n<2) return res;
	for(int i=2; i<=n; i++)
		res.push_back(i);
	int pos=0;
	while(res[pos]<=(int)sqrt(n))
	{
		/*for(int i=pos+1; i<res.size();)
		{
			if(!(res[i]%res[pos]))
			{
				res.erase(res.begin()+i);
				continue;
			}
			i++;
		}*/
		if(res[pos])
			for(int i=2; i<=n/res[pos]; i++)
				if(res[res[pos]*i-2])
					res[res[pos]*i-2]=0;
		pos++;
	}
	for(int i=0; i<res.size(); )
	{
		if(res[i]==0)
		{
			res.erase(res.begin()+i);
			continue;
		}
		i++;
	}
	return res;
}

int main()
{
	vector<int> res = primenumber(100);
	if(res.size()) cout << res[0];
	for(int i=1; i<res.size(); i++)
		cout << " " << res[i];
	cout << endl;
	system("pause");
	return 0;
}