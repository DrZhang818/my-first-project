#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s, t;
    cin >> s >> t;
    for(int i = 0; i < s.size(); i++) s[i] = tolower(s[i]);
    for(int i = 0; i < t.size(); i++) t[i] = tolower(t[i]);
    if(s < t) cout << -1;
    else if(s > t) cout << 1;
    else cout << 0;
    cout << "\n";
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
