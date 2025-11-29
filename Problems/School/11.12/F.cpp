#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<array<char,2>> Q(q);
    for(int i = 0; i < q; i++) {
        cin >> Q[i][0] >> Q[i][1];
    }
    int l = 0, r = n - 1;
    int ans = n;
    
    for(auto [ch, op] : Q) {
        
    }
    cout << ans << "\n";
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
