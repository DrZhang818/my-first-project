#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
	int n;
	cin >> n;
	vector<int> nums(n);
	for(int i = 0; i < n; i++){
		cin >> nums[i];
	}
	vector<int> pre(n), suf(n);
	pre[0] = suf[n - 1] = 0;
	for(int i = 1; i < n; i++){
		if(nums[i - 1] < nums[i]){
			pre[i] = pre[i - 1] + 1;
		}else if(nums[i - 1] == nums[i]){
			pre[i] = pre[i - 1];
		}else{
			pre[i] = 0;
		}
	}
	for(int i = n - 2; i >= 0; i--){
		if(nums[i + 1] < nums[i]){
			suf[i] = suf[i + 1] + 1;
		}else if(nums[i + 1] == nums[i]){
			suf[i] = suf[i + 1];
		}else{
			suf[i] = 0;
		}
	}
	for(int i = 0; i < n; i++){
		cout << max(pre[i], suf[i]) + 1 << " ";
	}
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	solve();

	return 0;
}