#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    sort(s.begin() + 1, s.end(), 
        [&](auto& x, auto& y) {
            return x.size() < y.size();
        });

    int ans = 0;
    set<string> st;
    for(int i = 1; i <= n; i++) {
        if(s[i].size() > s[i - 1].size() + 1) {
            break;
        }

        if(s[i].size() == 1) {
            ans = 1;
            st.insert(s[i]); 
        } else {
            int len = s[i].size() - 1;
            if(st.contains(s[i].substr(0, len)) && st.contains(s[i].substr(1, len))) {
                ans = s[i].size();
                st.insert(s[i]);
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}