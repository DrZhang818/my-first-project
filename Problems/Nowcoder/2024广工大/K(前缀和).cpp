#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

const int MOD = 1e9 + 7;
/*
    算法要求：   题目需要对每个奋斗事项的影响进行高效累加计算，直接模拟的时间复杂度为 𝑂(𝑛𝑚)
                在数据范围较大时不可行。
    优化方法：   需要使用前缀和、数学公式推导等技巧，将时间复杂度优化到 𝑂(𝑛+𝑚)
    涉及知识点： 前缀和的应用、数学建模与公式推导。这要求选手对算法和数学都有一定的理解和掌握。
    难度定位：   这种需要一定技巧和优化思路的题目，通常在 Codeforces 上属于
                Div.2 C 或 D 题，对应的 Rating 区间为 1500 至 1700 分。
*/
void solve(){
    int n, m;
    cin >> n >> m;

    vector<int> cnt1(n + 2, 0), cnt2(n + 2, 0);
    for(int i = 0; i < m; i++){
        int op, x;
        cin >> op >> x;
        if(op == 1) cnt1[x]++;
        else cnt2[x]++;
    }
    vector<ll> sumCnt1(n + 2, 0), sumCnt1x(n + 2, 0);
    vector<ll> sumCnt2(n + 2, 0), sumCnt2x(n + 2, 0), sumCnt2x2(n + 2, 0);

    for(int i = 1; i <= n; i++){
        sumCnt1[i] = sumCnt1[i - 1] + cnt1[i];
        sumCnt1x[i] = sumCnt1x[i - 1] + 1LL * cnt1[i] * i;
        
        sumCnt2[i] = sumCnt2[i - 1] + cnt2[i];
        sumCnt2x[i] = sumCnt2x[i - 1] + 1LL * cnt2[i] * i;
        sumCnt2x2[i] = sumCnt2x2[i - 1] + 1LL * cnt2[i] * i * i;
    }
    for(int d = 1; d <= n; d++){
        ll s1 = (d + 1LL) * sumCnt1[d] - sumCnt1x[d];
        ll s2 = (d + 1LL) * (d + 1LL) * sumCnt2[d] - 2LL * (d + 1LL) * sumCnt2x[d] + sumCnt2x2[d];
        ll total = (s1 + s2) % MOD;
        cout << total;
        if(d != n) cout << " ";
    }
    cout << endl;
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