#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<string> s(n + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i] >> a[i];
    }
    unordered_map<string,int> mp;
    for(int i = 1; i <= n; i++) {
        mp[s[i]] += a[i];
    }
    int mx = -inf;
    for(auto [_, x] : mp) {
        mx = max(mx, x);
    }
    unordered_map<string,int> cur;
    for(int i = 1; i <= n; i++) {
        if(mp[s[i]] != mx) {
            continue;
        }
        cur[s[i]] += a[i];
        if(cur[s[i]] >= mx) {
            cout << s[i] << "\n";
            return;
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
