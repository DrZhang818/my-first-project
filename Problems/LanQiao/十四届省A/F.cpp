#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P9234    
constexpr int inf = 1000000000;
void solve() { 
    int n;
    ll m;
    cin >> n >> m;
    m *= 2;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] *= 2;
    }
    sort(a.begin() + 1, a.end(), greater<ll>());
    vector<ll> suf(n + 2);
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + a[i];
    }
    int ans = inf;
    function<void(int,ll,int)> dfs = [&](int cnt, ll rem, int pos) -> void {
        if(rem == 0) ans = min(ans, cnt);
        if(suf[pos + 1] < rem) return;
        for(int i = pos + 1; i <= n; i++) {
            if(a[i] / 2 <= rem) dfs(cnt + 1, rem - a[i] / 2, i);
            if(a[i] <= rem) dfs(cnt, rem - a[i], i);  
        }
    };
    dfs(0, m, 0);
    if(ans == inf) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
