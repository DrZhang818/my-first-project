#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc116/tasks/abc116_d
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int t, d;
        cin >> t >> d;
        adj[t].push_back(d);
        a[i] = d;
    }
    vector<int> b{0};
    for(int i = 1; i <= n; i++) {
        if(adj[i].empty()) continue;
        sort(adj[i].begin(), adj[i].end(), greater<int>());
        b.push_back(adj[i][0]);
    }
    int sz = b.size() - 1;
    sort(b.begin() + 1, b.end(), greater<int>());
    sort(a.begin() + 1, a.end());
    ll ans = 0, sum = 0;
    for(int i = n; i >= n - k + 1; i--) {
        sum += a[i];
    }
    multiset<int> st;
    int r = n - k + 1;
    for(int x = 1; x <= min(k, sz); x++) {
        int pos = lower_bound(a.begin() + 1, a.end(), b[x]) - a.begin();
        if(pos > n - k) {
            st.insert(b[x]);
        } else {
            sum += b[x];
            while(r <= n && st.contains(a[r])) {
                st.erase(a[r]);
                r++;
            }
            if(r <= n) {
                sum -= a[r];
                r++; 
            }
        }
        ans = max(ans, sum + 1LL * x * x);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
