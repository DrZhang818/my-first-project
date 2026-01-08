#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    int v, w;
};

void solve() {  
    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    } 
    vector<Info> b(n + 1);
    for(int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        k -= y;
        b[i] = {x, z - y};
    }
    sort(b.begin() + 1, b.end(),
        [&](auto u, auto v) {
            return u.w < v.w;
        });
    multiset<int> st;
    for(int i = 1; i <= m; i++) {
        st.insert(a[i]);
    }
    int ans = 0;
    vector<bool> vis(n + 1);
    for(int i = n; i >= 1; i--) { 
        auto it = st.lower_bound(b[i].v);
        if(it != st.end()) {
            ans++;
            st.erase(it);
            vis[i] = true;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        if(k >= b[i].w) {
            ans++;
            k -= b[i].w;
        }
    }
    cout << ans << "\n";
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
