#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
/*
void differ(vector<int>& res, vector<int> nums, int& max, int pos, int diff, vector<int> sum)
{
	if(pos>=nums.size())
		return;
	sum.push_back(nums[pos]);
	int temp=pos;
	pos=find(nums.begin()+pos+1, nums.end(), nums[pos]+diff)-nums.begin();
	if(pos>=nums.size())
	{
		if(sum.size()>max)
		{
			res=sum;
			max=res.size();
		}
		if(sum.size()==1&&temp!=nums.size()-1)
		{
			sum.pop_back();
			differ(res, nums, max, temp, diff+1, sum);
		}
		return;
	}
	differ(res, nums, max, pos, diff, sum);
	if(sum.size()==1&&temp!=nums.size()-1)
	{
		//sum.pop_back();
		differ(res, nums, max, temp, diff+1, sum);
	}
}

vector<int> equaldiff(vector<int>& nums)
{
	int max=0;
	vector<int> res, temp;
	for(int i=0; i<nums.size(); i++)
		differ(res, nums, max, i, 0, temp);
	return res;
}
*/
const int MAX=1010;  
int dp[MAX][MAX];  
int longestSubSeq(vector<int> nums)  
{  
    int sz=nums.size();
	//vector<int> res, temp;
	//res.push_back(nums[0]);
    if (sz <= 1) return sz;  
  
    sort(nums.begin(),nums.end());  
  
    int ans=1;  
    int i,j;  
    for(i=0;i<MAX;i++)  
        for(j=0;j<MAX;j++)  
            dp[i][j]=1; //µ¥¶À³ÉÁÐ  
  
    for(i=1;i<sz;i++)  
    {  
        for(j=i-1;j>=0;j--)  
        {  
            int diff=nums[i]-nums[j];  
            dp[i][diff]=dp[j][diff]+1;  
            ans=max(ans,dp[i][diff]);  
			//if(ans>dp[i][diff])
        }  

    }  
    return ans;  
}  
int main()
{
	int num[] = {1, 2, 3, 4, 6, 8, 10, 14, 18, 22, 26, 30};
	vector<int> nums(num, num+sizeof(num)/sizeof(int));
	vector<int> res=equaldiff(nums);
	if(res.size()) cout << res[0];
	for(int i=1; i<res.size(); i++)
		cout << " " << res[i];
	cout << endl;
	system("pause");
	return 0;
}