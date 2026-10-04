#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void dedup(vector<vector<int>>& a, int n) {
    int k = a.size();
    if(k <= 1) return;

    vector<int> id(k), tmp(k);
    vector<int> cnt(n + 1), pos(n + 1), keys;
    iota(id.begin(), id.end(), 0);

    for(int j = n; j >= 1; j--) {
        keys.clear();
        for(int i : id) {
            int x = a[i][j];
            if(cnt[x]++ == 0) {
                keys.push_back(x);
            }
        }
        int cur = 0;
        for(int x : keys) {
            pos[x] = cur;
            cur += cnt[x];
        }
        for(int i : id) {
            int x = a[i][j];
            tmp[pos[x]++] = i;
        }
        id.swap(tmp);
        for(int x : keys) {
            cnt[x] = 0;
        }
    }

    vector<vector<int>> b;
    b.reserve(k);
    for(int i : id) {
        if(b.empty() || a[i] != b.back()) {
            b.push_back(move(a[i]));
        }
    }

    a = move(b);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> s;

    for(int i = 1; i <= m; i++) {
        vector<int> a(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        vector<vector<int>> ns;
        ns.reserve(2 * s.size() + 1);
        ns.push_back(a);

        for(const auto& p : s) {
            vector<int> q(n + 1);
            for(int j = 1; j <= n; j++) {
                q[j] = p[a[j]];
            }
            ns.push_back(move(q));
        }

        for(auto& p : s) {
            ns.push_back(move(p));
        }

        dedup(ns, n);
        s = move(ns);
    }

    cout << s.size() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
