#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, q;
    ll s;
    cin >> n >> q >> s;

    vector<int> t(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    vector<ll> st(n + 1);

    st[1] = s;
    for(int i = 2; i <= n; i++) {
        st[i] = st[i - 1] + t[i - 1];
    }

    for(int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        cout << st[x] + y - 1 << "\n";
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
