#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 2), d(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    vector<int> L(n + 2), R(n + 2);
    for(int i = 1; i <= n; i++) {
        L[i] = i - 1;
        R[i] = i + 1;
    }
    R[0] = 1;
    L[n + 1] = n;

    vector<int> dead(n + 2), vis(n + 2, -1), vec(n), ans(n);
    iota(vec.begin(), vec.end(), 1);

    for(int t = 0; t < n; t++) {
        vector<int> cur;
        for(int i : vec) {
            if(a[L[i]] + a[R[i]] > d[i]) {
                cur.push_back(i);
                dead[i] = true;
            }
        }

        ans[t] = cur.size();
        if(ans[t] == 0) break;

        vector<int> nvec;
        for(int i : cur) {
            for(int j : {L[i], R[i]}) {
                if(j < 1 || j > n || dead[j] || vis[j] == t) continue;
                vis[j] = t;
                nvec.push_back(j);
            }
        }

        for(int i : cur) {
            R[L[i]] = R[i];
            L[R[i]] = L[i];
        }

        vec = move(nvec);
    }

    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}