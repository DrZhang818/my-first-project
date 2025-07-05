#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1506/problem/D
/*
    构造 || 贪心 
    题意：
        给定一个长度为n的数组, 你可以进行以下操作
        op: 选择数组中两个不同的数, 并移除
        求出经过任意次操作后, 数组size的最小值
    关键思考:
        比较容易想到的贪心思路是:
            每次选择一个次数最大的数, 并与其他数配对
        这时候自然会出来两种情况:
        (1) 次数最大的数有着足够大的次数, 以至于在整个过程中始终是次数最大的, 这样
            答案就是cnt_max - (n - cnt_max) = 2 * cnt_max - n
        (2) 次数最大的数在操作过程中发生了转移, 这样
            在操作过程中, 一定会出现一个时刻: 记cnt1为次数最大数的次数, cnt2为次大的次数
            一定会出现cnt1 - cnt2 == 0的时刻
            这样最大和次大就会交替转化, 逐步消除其他数, 最终转化成两个数(最大和次大)之间
            反复操作, 而结果就是取决于在变成两个数后, cnt1是否等于cnt2
            直接思考并不容易, 但我们可以观察到以下性质:
            op操作每次会让sum_cnt -= 2
            因此sum_cnt的奇偶性始终不变
            从而有cnt1 + cnt2 == n (mod2)
            因此当n为奇数时, cnt1 - cnt2 一定是1
                当n为偶数时, cnt1 == cnt2
            所以, 答案就是 n % 2
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int, int> c;
    int mx = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        c[a[i]]++;
        mx = max(mx, c[a[i]]);
    }
    cout << max(mx * 2 - n, n % 2) << "\n";
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
