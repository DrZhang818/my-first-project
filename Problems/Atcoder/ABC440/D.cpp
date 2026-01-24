#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    while(q--) {
        int x, y;
        cin >> x >> y;
        int L = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
        int lo = x - 1, hi = numeric_limits<int>::max();
        while(lo + 1 < hi) {
            int m = lo + (hi - lo) / 2;
            auto R = lower_bound(a.begin() + 1, a.end(), m) - a.begin();
            if(m - x + 1 - R + L <= y) {
                lo = m;
            } else {
                hi = m;
            }
        }
        cout << lo << "\n";
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
