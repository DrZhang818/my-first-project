#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2040/problem/C
/*
    贪心思维(贡献法) || 构造
    考虑每个数对S(p)的贡献:
        1.
        当1在两端时, 贡献是n
        当1在中间时, 贡献是l * (n - l + 1), 其中l是1左边的长度(包含1) 
        不难发现, l * (n - l + 1) 一定大于n
        因此1的贡献多就会导致别的数的贡献少, 导致S变小
        因此最优解一定是1放在两端
        2.
        在确定了1的位置后, 剩下就是解决2 - n的排列问题
        这是一个规模更小的子问题, 因此结论相同, 由此可以递归解决所有子问题 
    思考1: 总方案数
        因此对于1~n的排列, 前n-1个数都有两种放法, 因此合法方案数为2^(n-1)个
        由于2^60已经大于10^19, 而k最大为10^12, 因此可以预先判定n>=60的情况不成立
    思考2: 第K个方案如何构造
        对于1, 放左边的方案有2^(n - 1 - 1)种, 右边也是如此
            let cur = (1LL << (n - 1 - 1))
            那么k < cur时放左边, 否则放右边
        核心在于1到2之间的转移
            当1在左边时, k的大小就是2~(n-1)的排列方案
            当1在右边时, (k - cur)的大小就是2~(n-1)的排列方案        
*/
void solve(){
    int n;
    ll k;
    cin >> n >> k;
    k--;
    if(n <= 60 && k >= (1LL << (n - 1))){
        cout << -1 << "\n";
        return;
    }
    vector<int> nums(n);
    int l = 0, r = n - 1;
    for(int i = 1; i < n; i++){
        if(n - 1 - i > 60 || k < (1LL << (n - 1 - i))){
            nums[l++] = i;
        }
        else{
            nums[r--] = i;
            k -= (1LL << (n - 1 - i));
        }
    }
    nums[l] = n;
    for(auto& num : nums){
        cout << num << " ";
    }
    cout << "\n";
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