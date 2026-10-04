#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int inf = 1E9;

vector<int> zFunction(const string& s) {
    string t = " " + s;
    int n = s.size();
    vector<int> z(n + 1);
    z[1] = n;
    for(int i = 2, l = 1, r = 0; i <= n; i++) {
        if(i <= r) {
            z[i] = min(z[i - l + 1], r - i + 1);
        }
        while(i + z[i] <= n && t[1 + z[i]] == t[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

void solve() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    vector<int> w(n + 1);
    vector<i64> prew(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
        prew[i] = prew[i - 1] + w[i];
    }

    vector<pair<int, int>> Q(m);
    for(auto& [l, r] : Q) {
        cin >> l >> r;
    }

    vector<int> id(m);
    iota(id.begin(), id.end(), 0);

    sort(id.begin(), id.end(), 
        [&](auto& i, auto& j) {
            return Q[i].second < Q[j].second;
        });

    set<int> st;
    for(int i = 1; i <= n + 1; i++) {
        st.insert(i);
    }

    auto z = zFunction(s + "#" + t);

    s = "#" + s;
    vector<int> pi(n + 1);
    for(int i = 2; i <= n; i++) {
        int j = pi[i - 1];
        while(j && s[j + 1] != s[i]) j = pi[j];
        pi[i] = s[j + 1] == s[i] ? j + 1 : 0;
    }

    vector<vector<int>> del(n + 1);
    vector<i64> g(n + 1), dp(n + 1), A(n + 1);
    for(int i = 1; i <= n; i++) {
        g[i] = w[i] + g[pi[i]];
        dp[i] = dp[i - 1] + g[i];
        
        int b = z[n + 1 + i];
        A[i] = A[i - 1] + prew[b];
        del[i + b - 1].push_back(i);
    }

    vector<i64> ans(m);
    int idx = 0;
    for(int i : id) {
        auto [l, r] = Q[i];
        while(idx < r) {
            for(int x : del[idx]) st.erase(x);
            idx++;
        }
            
        int p = min(r + 1, *st.lower_bound(l));
        ans[i] = A[p - 1] - A[l - 1] + dp[r - p + 1];
    }   

    for(int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}