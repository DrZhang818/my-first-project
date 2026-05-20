#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 1), tag(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        tag[x] = 1;
    }

    vector<int> x, y;
    for(int i = 1; i <= n; i++) {
        if(tag[i]) {
            x.push_back(i);
        } else {
            y.push_back(i);
        }
    }

    vector<pair<int,int>> ans;
    for(int u : y) {
        bool ok = false;
        for(int v : x) {
            if(a[u] % a[v] == k || a[v] % a[u] == k) continue;
            ok = true;
            ans.emplace_back(u, v);
            ans.emplace_back(v, v);
            break;
        }
        if(!ok) {
            cout << "NO\n";
            return;
        }
    }

    auto [s, t] = [&] {
        for(int i = 0; i < x.size(); i++) {
            for(int j = i + 1; j < x.size(); j++) {
                int u = x[i], v = x[j];
                if(a[u] % a[v] != k && a[v] % a[u] != k) {
                    return pair{u, v};
                }
            }
        }
        return pair{-1, -1};
    }();

    if(s == -1) {
        if(x.size() > 1) {
            cout << "NO\n";
            return;
        }
        ans.emplace_back(x[0], x[0]);
    } else {
        ans.emplace_back(s, t);
        ans.emplace_back(s, s);
        for(int u : x) {
            if(u == s || u == t) continue;
            ans.emplace_back(u, u);
            ans.emplace_back(t, t);
            ans.emplace_back(s, t);
            ans.emplace_back(s, s);
        }
        ans.emplace_back(s, s);
    }

    cout << "YES\n";
    cout << ans.size() << "\n";
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
