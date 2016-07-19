#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& A, int p, int q, int r)
{
//	if(r<=q)
//		return;
	int n1=q-p+1, n2=r-q;
	vector<int> L(A.begin()+p, A.begin()+q+1);
	vector<int> R(A.begin()+q+1, A.begin()+r+1);
	L.push_back(INT_MAX);
	R.push_back(INT_MAX);
	int i=0, j=0;
	for(int k=p; k<=r; k++)
	{
		if(L[i]<=R[j])
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
}

void guibing_sort(vector<int>& A, int s, int e)
{
	if(e<=s)
		return;
	guibing_sort(A, s, s+(e-s)/2);
	guibing_sort(A, s+(e-s)/2+1, e);
	merge(A, s, s+(e-s)/2, e);
}

int main()
{
	int a[] = {1, 3, 2, 5, 4, 8, 4};
	vector<int> A(a, a+sizeof(a)/sizeof(int));
	guibing_sort(A, 0, A.size()-1);
	if(A.size())
		cout << A[0];
	for(int i=1; i<A.size(); i++)
		cout << " " << A[i];
	cout << endl;
	system("pause");
	return 0;
}