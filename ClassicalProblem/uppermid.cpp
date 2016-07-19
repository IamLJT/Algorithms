#include <iostream>
#include <vector>
using namespace std;

int uppermid(vector<int> A, int a1, int a2, vector<int> B, int b1, int b2)
{
	int len=a2-a1+1;
	if(A[(a2+a1)/2]==B[(b2+b1)/2])
		return A[(a2+a1)/2];
	if(len==1)
		return A[(a2+a1)/2]<B[(b2+b1)/2]?A[(a2+a1)/2]:B[(b2+b1)/2];
	if(A[(a2+a1)/2]>B[(b2+b1)/2])
	{
		a2=(a2+a1)/2;
		if(len%2)
			b1=(b2+b1)/2;
		else
			b1=(b2+b1)/2+1;
	}
	else
	{
		b2=(b2+b1)/2;
		if(len%2)
			a1=(a2+a1)/2;
		else
			a1=(a2+a1)/2+1;
	}
	return uppermid(A, a1, a2, B, b1, b2);
}

int min0(int n1, int n2)
{
	return n1<n2?n1:n2;
}

int max0(int n1, int n2)
{
	return n1>n2?n1:n2;
}

int Kmin(vector<int> M, vector<int> N, int k)
{
	int m=M.size(), n=N.size();
	if(m==0) return N[min0(n, k)];
	if(n==0) return M[min0(m, k)];
	if(k==1) return M[0]<N[0]?M[0]:N[0];
	if(k>=m+n) return M.back()>N.back()?M.back():N.back();
	if(k<min0(m, n)) return uppermid(M, 0, k-1, N, 0, k-1);
	else if(k>max0(m, n))
	{
		if(M[k-n-1]>=N.back()) return M[k-n-1];
		if(N[k-m-1]>=M.back()) return N[k-m-1];
		return uppermid(M, k-n, m-1, N, k-m, n-1);
	}
	else
	{
		if(m>n)
		{
			if(M[k-n-1]>=N.back()) return M[k-n-1];
			return uppermid(M, k-n, k-1, N, 0, n);
		}
		else
		{
			if(N[k-m-1]>=M.back()) return N[k-m-1];
			return uppermid(M, 0, m, N, k-m, k-1);
		}
	}
	return -1;
}

int main()
{
	int N1, N2;
	cin >> N1 >> N2;
	vector<int> A(N1, 0),B(N2, 0);
	for(int i=0; i<N1; i++)
		cin >> A[i];
	for(int i=0; i<N2; i++)
		cin >> B[i];
	//cout << uppermid(A, 0, A.size()-1, B, 0, B.size()-1) << endl;
	int k;
	cin >> k;
	cout << Kmin(A, B, k) << endl;
	system("pause");
	return 0;
}