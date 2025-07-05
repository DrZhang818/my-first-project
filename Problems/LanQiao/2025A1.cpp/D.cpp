#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dfs(int n, int m, bool tag) {
    ll sz = (1LL << n - 1);
    if(sz == 1) return tag;
    if(m <= (sz >> 1)) return dfs(n - 1, m, tag);
    else return dfs(n - 1, m - (sz >> 1), tag ^ 1);
}
void solve() {
    int q;
    cin >> q;
    while(q--) {
        int n, m;
        cin >> n >> m;
        if(dfs(n, m, 1)) {
            cout << "RED\n"; 
        } else {
            cout << "BLACK\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
