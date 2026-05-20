#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

int fac[13];

void solve() {
    int n, q;
    cin >> n >> q;

    vector<pair<i64, i64>> items;
    vector<int> cnt(10);

    auto dfs = [&](this auto&& self, int d, int rem) -> void {
        if(d == 9) {
            cnt[9] = rem;
            i64 a = 0, b = 0;
            for(int i = 0; i <= 9; i++) {
                for(int j = 0; j < cnt[i]; j++) a = a * 10 + i;
            }
            for(int i = 9; i >= 0; i--) {
                for(int j = 0; j < cnt[i]; j++) b = b * 10 + i;
            }

            i64 ways = fac[n];
            for(int i = 0; i <= 9; i++) {
                ways /= fac[cnt[i]];
            }

            items.emplace_back(b - a, ways);
            return;
        }
        for(int i = 0; i <= rem; i++) {
            cnt[d] = i;
            self(d + 1, rem - i);
        }
    };
    dfs(0, n);

    sort(items.begin(), items.end());

    vector<i64> V, dp;
    for(int i = 0, j = 0; i < items.size(); i = j) {
        i64 sum = 0;
        while(j < items.size() && items[j].first == items[i].first) {
            sum += items[j].second;
            j++;
        }
        V.push_back(items[i].first);
        dp.push_back(sum);
    }

    int m = V.size();
    vector<int> nxt(m);
    vector<int> deg(m);

    for(int i = 0; i < m; i++) {
        i64 v = V[i];
        array<int, 10> c {};
        for(int j = 0; j < n; j++) {
            c[v % 10]++;
            v /= 10;
        }
        i64 a = 0, b = 0;
        for(int j = 0; j <= 9; j++) {
            for(int k = 0; k < c[j]; k++) a = a * 10 + j;
        }
        for(int j = 9; j >= 0; j--) {
            for(int k = 0; k < c[j]; k++) b = b * 10 + j;
        }
        i64 nv = b - a;
        nxt[i] = lower_bound(V.begin(), V.end(), nv) - V.begin();
        deg[nxt[i]]++;
    }

    queue<int> que;

    for(int i = 0; i < m; i++) {
        if(deg[i] == 0) {
            que.push(i);
        }
    }

    vector<bool> in_cycle(m, true);

    while(!que.empty()) {
        int u = que.front();
        que.pop();
        in_cycle[u] = false;
        int v = nxt[u];
        dp[v] += dp[u];
        if(--deg[v] == 0) {
            que.push(v);
        }
    }

    vector<bool> vis(m);
    for(int i = 0; i < m; i++) {
        if(in_cycle[i] && !vis[i]) {
            vector<int> cyc;
            int cur = i;
            while(!vis[cur]) {
                vis[cur] = true;
                cyc.push_back(cur);
                cur = nxt[cur];
            }
            i64 sum = 0;
            for(int u : cyc) sum += dp[u];
            for(int u : cyc) dp[u] = sum;
        }
    }

    while(q--) {
        i64 y;
        cin >> y;
        auto it = lower_bound(V.begin(), V.end(), y);
        if(it != V.end() && *it == y) {
            int id = it - V.begin();
            if(in_cycle[id]) {
                cout << dp[id] << "\n"; 
            } else {
                cout << dp[id] + 1 << "\n";
            }
        } else {
            cout << 1 << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= 12; i++) {
        fac[i] = fac[i - 1] * i;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
