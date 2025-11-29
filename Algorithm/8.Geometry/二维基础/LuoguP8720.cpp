#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<array<int,2>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    sort(a.begin() + 1, a.end());
    a.erase(unique(a.begin() + 1, a.end()), a.end());
    n = a.size() - 1;
    using T = pair<db,db>;
    ll ans = 1;
    for(int i = 1; i <= n; i++) {
        ll cur = 1;
        auto [k1, b1] = a[i];
        set<T> st;
        for(int j = i - 1; j >= 1; j--) {
            auto [k2, b2] = a[j];
            if(k1 == k2) {
                continue;
            }
            db x = db(b2 - b1) / db(k1 - k2);
            db y = k1 * x + b1;
            if(!st.contains({x, y})) {
                cur++;                                                
                st.insert({x, y});
            }
        }
        ans += cur;   
    }
    cout << ans << "\n";
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
