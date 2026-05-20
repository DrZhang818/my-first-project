#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    set<int> st;
    for(int i = 1; i <= n; i++) {
        st.insert(a[i]);
    }
    while(q--) {
        int k;
        cin >> k;
        vector<int> range(k);
        for(int i = 0; i < k; i++) {
            cin >> range[i];
        }
        for(int i : range) {
            st.erase(a[i]);
        }
        cout << *st.begin() << "\n";
        for(int i : range) {
            st.insert(a[i]);
        }
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
