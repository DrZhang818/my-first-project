#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2040/problem/A
/*
    数学 || 分组哈希
    题意: 给定数组nums 和 一个整数k, 求出cnt[num % k] == 1的num的下标
          如果没有, 输出-1
    关键优化:
        对原数组进行模k操作, 这样后面就可以直接与cnt建立对应关系, 从而无需再次遍历求下标
    特别注意:
        本题是1-index, 输出时要加1
*/

void solve1(){
    int n, k;
    cin >> n >> k;
    vector<int> nums(n), cnt(k);
    for(auto& num : nums){
        cin >> num;
        num %= k;
        cnt[num]++;
    }
    for(int i = 0; i < n; i++){
        if(cnt[nums[i]] == 1){
            cout << "YES\n" << i + 1 << "\n";
            return;
        }
    }
    cout << "NO\n";
}   


//比赛写法
void solve(){
    int n, k;
    cin >> n >> k;
    std::vector<int> nums(n);
    vector<int> mod(k);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        mod[(nums[i] % k)]++;
    }
    for(int i = 0; i < k; i++){
        if(mod[i] == 1){
            cout << "YES\n";
            for(int p = 0; p < n; p++){
                if(nums[p] % k == i){
                    cout << p + 1 << "\n";
                }
            }
            return ;
        }
    }
    cout << "NO\n";

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}