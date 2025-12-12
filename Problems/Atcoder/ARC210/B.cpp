#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    multiset<int> low, mid, high;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        mid.insert(a[i]);
    }
    for(int i = 1; i <= m; i++) {
        mid.insert(b[i]);
    }
    while(q--) {
        int op, i, x;
        cin >> op >> i >> x;
        int y = op == 1 ? a[i] : b[i];
        op == 1 ? a[i] = x : b[i] = x;
        if(!low.empty() && y <= *low.rbegin()) low.erase(low.find(y)), ans -= y;
        else if(!mid.empty() && y <= *mid.rbegin()) mid.erase(mid.find(y));
        else high.erase(high.find(y)), ans -= y;

        mid.insert(x);
        
        if(low.size() == n / 2 && *low.rbegin() > *mid.begin()) {
            mid.insert(*low.rbegin());
            ans -= *low.rbegin();
            low.erase(prev(low.end()));
        }
        if(high.size() == n / 2 && *high.begin() < *mid.rbegin()) {
            mid.insert(*high.begin());
            ans -= *high.begin();
            high.erase(high.begin());
        }
        while(low.size() < n / 2) {
            auto it = mid.begin();
            low.insert(*it);
            ans += *it;
            mid.erase(it);
        } 
        while(high.size() < n / 2) {
            auto it = prev(mid.end());
            high.insert(*it);
            ans += *it;
            mid.erase(it);
        }
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
