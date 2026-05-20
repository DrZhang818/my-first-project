#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    set<pair<string,string>> st;
    bool ok = false;
    for(int i = 1; i <= n; i++) {
        string s, t;
        cin >> s >> t;
        auto cur = make_pair(s, t);
        if(st.find(cur) != st.end()) {
            ok = true;
        }
        st.insert(cur);
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
