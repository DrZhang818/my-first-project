#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        if(s.substr(i) + s.substr(0, i) == t) {
            cout << "Yes\n";
            return; 
        }
    }
    cout << "No\n";
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
