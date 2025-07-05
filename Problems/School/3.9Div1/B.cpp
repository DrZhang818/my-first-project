#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> cnt(n + 1, 1);
    vector<int> ok(n + 1, false);
    ok[1] = true;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cnt[u] -= 1;
        cnt[v] += 1;
        ok[v] |= ok[u];
        if(cnt[u] == 0) ok[u] = false;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(ok[i] && cnt[i] >= 1) {
            ans += 1;
        }
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
    
