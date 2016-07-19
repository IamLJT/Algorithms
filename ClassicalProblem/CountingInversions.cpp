#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

typedef long long ll;

ll countmerge(vector<int>& A, int p, int q, int r)
{
//	if(r<=q)
//		return;
	int n1=q-p+1, n2=r-q;
	vector<int> L(A.begin()+p, A.begin()+q+1);
	vector<int> R(A.begin()+q+1, A.begin()+r+1);
	L.push_back(INT_MAX);
	R.push_back(INT_MAX);
	int i=0, j=0;
	ll count=0;
	for(int k=p; k<=r; k++)
	{
		if(L[i]<=R[j])
			A[k] = L[i++];
		else
		{
			A[k] = R[j++];
			if(L[i]!=INT_MAX)
				count+=(L.size()-i-1);
		}
	}
	return count;
}

ll countinv(vector<int>& A, int s, int e)
{
	if(e<=s)
		return 0;
	ll x=countinv(A, s, s+(e-s)/2);
	ll y=countinv(A, s+(e-s)/2+1, e);
	ll z=countmerge(A, s, s+(e-s)/2, e);
	return x+y+z;
}

int main()
{
	//int a[] = {1, 3, 2, 5, 4, 8, 4};
	//vector<int> A(a, a+sizeof(a)/sizeof(int));
	int N=100000;
	vector<int> A;
//	for(int i=0; i<N; i++)
//		cin >> A[i];
	ifstream fin("C:\\Users\\Iam_luffy\\Desktop\\1.txt");
	int i=0;
	while(!fin.eof())
	{
		fin>>i;
		A.push_back(i);
	}
	cout << countinv(A, 0, A.size()-1) << endl;
	/*if(A.size())
		cout << A[0];
	for(int i=1; i<A.size(); i++)
		cout << " " << A[i];
	cout << endl;*/
	system("pause");
	return 0;
}
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//using namespace std;
//
//double countInversion(vector<double> & vec);
//double merge(vector<double> & vec, vector<double> & v1, vector<double> & v2);
//
//int main() {
//        ifstream fin("C:\\Users\\Iam_luffy\\Desktop\\1.txt");
//        vector<double> init;
//        double temp;
//        
//        //为什么用这个while循环，vector里最后一个数字会出现两遍
//        //while(!fin.eof()) {
//        //        fin>>temp;
//        //        init.push_back(temp); 
//        //}
//
//        for(int p = 0; p < 100000; p++) {
//                fin>>temp;
//                init.push_back(temp);
//        }
//
//        double dataSize = init.size();
//        cout<<dataSize<<endl; 
//
//        double x = countInversion(init);
//        char str[20];
//        sprintf(str,"%.8lf",x); 
//        printf("%s",str);
//		system("pause");
//        return 0;
//}
//
//
//
//double countInversion(vector<double> & vec) {
//        double n = vec.size();
//        if( (n - 1) <  0.0000001 ) return 0;
//        
//        double result = 0;
//        double mid = n / 2;
//
//        vector<double> v1, v2;
//
//        double k = 0;
//        while( k < n) {
//                if(k < mid) {
//                        v1.push_back(vec[k]);
//                        k += 1;
//                } else {
//                        v2.push_back(vec[k]);
//                        k += 1;
//                }
//        }
//
//        double c1 = countInversion(v1);
//        double c2 = countInversion(v2);
//
//        vec.clear();
//        double c3 = merge(vec, v1, v2);
//
//        result = c1 + c2 + c3;
//        return result;
//}
//
//double merge(vector<double> & vec, vector<double> & v1, vector<double> & v2) {
//        double ans = 0;
//
//        long n1 = v1.size();
//        long n2 = v2.size();
//
//        long p1 = 0;
//        long p2 = 0;
//
//        double size = n1 + n2;
//        for(double k = 0; k < size && p1 < n1 && p2 < n2; k++) {
//                if(v1[p1] <= v2[p2]) {
//                        vec.push_back(v1[p1]);
//                        p1 += 1;
//                } else {
//                        vec.push_back(v2[p2]);
//                        p2 += 1;
//                        ans += n1 - p1;
//                }
//        }
//
//        while(p1 < n1) { 
//                vec.push_back(v1[p1]); 
//                p1 += 1; }
//
//        while(p2 < n2) {
//                vec.push_back(v2[p2]);
//                p2 += 1;
//        }
//
//        return ans;
//} 
