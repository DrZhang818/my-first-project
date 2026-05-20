#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int c0 = count(s.begin(), s.end(), '0') + 1;
    if(c0 == 1 || c0 == 2 && s.back() != '0') {
        cout << -1 << "\n";
        return;
    }

    vector<pair<int,int>> ans;

    for(int i = 0, u = 1, w = 1; i < s.size(); i++) {
        int v = i + 2;
        if(s[i] == '0') {
            ans.emplace_back(w, v);
            w = v;
        } else {
            ans.emplace_back(u, v);
            u = v;
        }
        if(i == s.size() - 1) {
            ans.emplace_back(u, n);
            if(c0 > 2) {
                ans.emplace_back(w, 1);
            }
        }
    }

    cout << ans.size() << "\n";
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}