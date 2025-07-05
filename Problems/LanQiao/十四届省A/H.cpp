#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P9236
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    ll ans = 0;
    for(int d = 0; d <= 20; d++) {
        vector<int> cnt(2);
        for(int i = 0; i <= n; i++) cnt[a[i] >> d & 1]++;
        ans += (1LL << d) * cnt[0] * cnt[1];
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
