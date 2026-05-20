#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int cur = *max_element(a.begin() + 1, a.end());
    while(m--) {
        char op;
        cin >> op;
        int l, r;
        cin >> l >> r;
        if(l <= cur && cur <= r) {
            if(op == '+') {
                cur++;
            } else {
                cur--;
            }
        }
        cout << cur << " \n"[m == 0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
