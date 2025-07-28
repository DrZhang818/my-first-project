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
    map<string,int> mp;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        if(!mp[s]) {
            cout << "OK\n";
        } else {
            cout << s << mp[s] << "\n";
        }
        mp[s]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
