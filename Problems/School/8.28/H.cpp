#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> pos(n + 1, {0});
    for(int i = 1; i <= m; i++) {
        int T, P;
        cin >> T >> P;
        pos[P].push_back(T);
    }
    vector<vector<ll>> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        int m = pos[i].size();
        pre[i].resize(m + 1);
        for(int j = 1; j <= m; j++) {
            pre[i][j] = pre[i][j - 1];
            if(j % 2 == 0) {
                pre[i][j] += pos[i][j] - pos[i][j - 1];
            }
        }
    }
    map<PII,ll> mp;    
    int q;
    cin >> q;
    while(q--) {
        int A, B;
        cin >> A >> B;
        if(pos[A].size() >= pos[B].size()) {
            swap(A, B);
        }
        PII cur = {A, B};
        if(mp.contains(cur)) {
            cout << mp[cur] << "\n";
            continue;
        }
        ll ans = 0;
        int m = pos[A].size() - 1;
        for(int i = 1; i <= m; i++) {
            int j = lower_bound(pos[B].begin() + 1, pos[B].end(), pos[A][i]) - pos[B].begin() - 1;
            ll add = pre[B][j];
            if(j & 1) {
                add += pos[A][i] - pos[B][j];
            }
            if(i & 1) {
                add = -add;
            }
            ans += add;
        }
        mp[cur] = ans;
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
