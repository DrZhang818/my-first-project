#include<bits/stdc++.h>
using namespace std;

void merge(vector<int>& nums, int l, int m, int r);
void mergeSort(vector<int>& nums, int l, int r){
	if(l >= r) return;
	int m = l + (r - l) / 2;
	mergeSort(nums, l, m);
	mergeSort(nums, m + 1, r);
	merge(nums, l, m, r);
}
void merge(vector<int>& nums, int l, int m, int r){
	if(l == r) return;
	vector<int> help(r - l + 1);
	int i = l, j = m + 1, k = 0;

	while(i <= m && j <= r){
		if(nums[i] < nums[j]){
			help[k++] = nums[i++];
		}else{
			help[k++] = nums[j++];
		}
	}
	while(i <= m){
		help[k++] = nums[i++];
	}
	while(j <= r){
		help[k++] = nums[j++];
	}
	for(int p = 0; p < help.size(); p++){
		nums[l + p] = help[p];
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; 
	cin >> n;
	vector<int> nums(n);
	for(auto& num : nums){
		cin >> num;
	}	
	mergeSort(nums, 0, nums.size() - 1);
	for(auto& num : nums){
		cout << num <<' ';
	}
	cout << endl; 
	return 0;
}