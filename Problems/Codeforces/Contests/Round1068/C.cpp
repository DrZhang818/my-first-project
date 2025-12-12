#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    set<int> st;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    sort(a.begin() + 1, a.end());
    a.erase(unique(a.begin() + 1, a.end()), a.end());
    set<int> vis;
    vector<int> ans;
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        if(!vis.contains(x)) {
            ans.push_back(x);
            for(int j = 1; 1LL * x * j <= k; j++) {
                if(!st.contains(x * j)) {
                    cout << -1 << "\n";
                    return;
                }
                vis.insert(x * j);     
            }
        }
    }
    cout << ans.size() << "\n";
    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
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
