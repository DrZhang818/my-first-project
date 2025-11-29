#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> X(n + 1), Y(m + 1);
    vector<array<int,2>> xy(n * m + 1);
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        cin >> X[i];
        if(xy[X[i]][0]) {
            ok = false;
        }
        xy[X[i]][0] = i;
    }
    for(int j = 1; j <= m; j++) {
        cin >> Y[j];
        if(xy[Y[j]][1]) {
            ok = false;
        }
        xy[Y[j]][1] = j;
    }
    if(!ok) {
        cout << "No\n";
        return;
    }
    vector mn(n + 1, vector<int>(m + 1, n * m));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            mn[i][j] = min(mn[i][j], X[i]);
        }
    }   
    for(int j = 1; j <= m; j++) {
        for(int i = 1; i <= n; i++) {
            mn[i][j] = min(mn[i][j], Y[j]);
        }
    }
    set<int> st;
    for(int i = 1; i <= n * m; i++) {
        st.insert(i);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x = mn[i][j];
            auto it = st.upper_bound(x);
            while(1) {
                if(it == st.begin()) {
                    cout << "No\n";
                    return;
                }
                it = prev(it);
                int cur = *it;
                auto [u, v] = xy[cur];
                if((u == 0 || u == i) && (v == 0 || v == j)) {
                    break;
                }
            }
            mn[i][j] = *it;
            st.erase(it);
        }
    }
    cout << "Yes\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << mn[i][j] << " \n"[j == m];
        }
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
