#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> f(10005);
    for(int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        cin >> f[t];
    }
    vector<vector<int>> Q(10005);
    for(int i = 1; i <= q; i++) {
        int t;
        cin >> t;
        Q[t].push_back(i);
    }
    vector<int> ans(q + 1);
    int cur = 1, dir = 1;
    set<int> st;
    for(int t = 0; t <= 10000; t++) {
        for(int v : Q[t]) ans[v] = cur; 
        if(f[t]) st.insert(f[t]);
        st.erase(cur);
        if(st.empty()) continue;
        if(dir) {
            auto it = st.lower_bound(cur);
            if(it == st.end()) {
                cur--;
                dir = 0;
            } else {
                cur++;
            }
        } else {
            auto it = st.lower_bound(cur);
            if(it == st.begin()) {
                cur++;
                dir = 1;
            } else {
                cur--;
            }
        }
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
