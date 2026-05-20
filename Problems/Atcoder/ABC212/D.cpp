#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {
    int q;
    cin >> q;

    multiset<i64> st;
    i64 d = 0;

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            i64 x;
            cin >> x;
            st.insert(x - d);
        } else if(op == 2) {
            i64 x;
            cin >> x;
            d += x;
        } else {
            auto it = st.begin();
            cout << (*it) + d << "\n";
            st.erase(it);
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
