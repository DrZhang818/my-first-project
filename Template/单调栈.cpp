#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int, int>;

vector<int> MonotoneStk(vector<int> &nums){
	int n = nums.size();
	vector<int> ans(n, 0);
	stack<int> stk;
	for(int i = n; i >= 1; i--){
		while(!stk.empty() && nums[stk.top() - 1] <= nums[i - 1]){
			stk.pop();
		}
		if(!stk.empty()){
			ans[i - 1] = stk.top();
		}
		stk.push(i);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector<int> nums(n);
	for(auto &num : nums){
		cin >> num;
	}
	auto ans = MonotoneStk(nums);
	for(auto &num : ans){
		cout << num << " ";
	}
	cout << "\n";
	return 0;
}