#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1771/B
constexpr int inf = 1000000000;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> end(n + 1, inf);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        end[u] = min(end[u], v);
    }
    ll ans = 0;
    int cur = n + 1;
    for(int i = n; i >= 1; i--) {
        cur = min(cur, end[i]);
        ans += cur - i;
    }   
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
