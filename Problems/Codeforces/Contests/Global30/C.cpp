#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> b(m + 1), c(m + 1);
    vector<int> p0, p1;    
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> c[i];
        if(c[i]) {
            p1.push_back(i);
        } else {
            p0.push_back(i);
        }
    }
    int ans = 0;
    sort(p1.begin(), p1.end(), 
        [&](auto x, auto y) {
            return b[x] < b[y];
        });
    multiset<int> st(a.begin() + 1, a.end());
    for(auto i : p1) {
        auto it = st.lower_bound(b[i]);
        if(it == st.end()) {
            break;
        }
        ans++;
        int x = max(*it, c[i]);
        st.erase(it);
        st.insert(x);
    }
    sort(p0.begin(), p0.end(), 
        [&](auto x, auto y) {
            return b[x] < b[y];
        });
    for(auto i : p0) {
        auto it = st.lower_bound(b[i]);
        if(it == st.end()) {
            break;
        }
        ans++;
        st.erase(it);
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
