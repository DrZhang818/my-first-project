#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2048/problem/B
/*
    构造最小权值排列以最小化所有长度为 K 的子数组的最小值之和
    贪心思维
    题意: 给定两个正整数n和K, 定义一个数组的权值为数组中最小的数
          要求构造出一种合法的长度为n的排列, 使得所有长度为k的子数组的权值之和最小
    关键思考:
        考虑贡献法:
            贪心的想, 我们希望1贡献的次数尽可能多, n贡献的次数尽可能少
            而1的贡献次数主要由1所在的位置决定
            当1处于第K个位置的时候, 正好可以贡献K次
                换句话说, 当1处于前K-1个位置的时候, 贡献的次数都要更小, 使答案变劣
            那么当1放在K的时候, 1 ~ K的为左端点的子数组全部被覆盖
            所以在考虑2的时候应该放在pos(1) + K 的位置以覆盖K + 1 ~ 2K的数组
        于是剩下所有的位置可以递归完成, 问题解决
*/
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    int cur = 1;
    for(int i = k - 1; i < n; i += k){
        nums[i] = cur++; 
    }
    for(int i = 0; i < n; i++){
        if(nums[i] != 0) continue;
        nums[i] = cur++;
    }
    for(auto num : nums){
        cout << num << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
