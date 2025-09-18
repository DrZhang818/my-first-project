#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    unordered_map<string,int> mp;
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        mp[s]++;
        mx = max(mx, mp[s]);
    }
    for(auto &[s, c] : mp) {
        if(c == mx) {
            cout << s << "\n";
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
