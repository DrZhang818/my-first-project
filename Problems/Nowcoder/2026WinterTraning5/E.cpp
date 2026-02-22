#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, p;
    cin >> n >> p;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] + a[i]) % p;
    }

    set<PII> st;

    st.insert({0, 0});

    int L = -1, R = -1;
    int ans = -1;
    for(int i = 1; i <= n; i++) {
        if(pre[i] > ans) {
            ans = pre[i];
            L = 0;
            R = i - 1;
        }

        auto it = st.upper_bound({pre[i], 0});
        if(it != st.end()) {
            int x = it->first;
            int cur = (pre[i] - x + p) % p;
            if(cur > ans) {
                ans = cur;
                L = it->second;
                R = i - 1;
            }
        }

        st.insert({pre[i], i});
    }

    cout << L << " " << R << " " << ans << "\n";
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
