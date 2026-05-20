#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    vector<int> a;
    for(int i = n; i >= 1; i--) {
        int pos = a.size();
        int cnt = 0;

        while(pos > 0 && cnt < d[i]) {
            pos--;
            if(p[a[pos]] > p[i]) {
                cnt++;
            }
        }

        if(cnt < d[i]) {
            cout << -1 << "\n";
            return;
        }

        a.insert(a.begin() + pos, i);
    }

    assert(a.size() == n);
    vector<int> ans(n + 1);
    for(int i = 0; i < n; i++) {
        ans[a[i]] = i + 1;
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}