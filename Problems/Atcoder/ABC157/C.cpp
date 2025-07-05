#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, -1);
    bool ok = true;
    for(int i = 1; i <= m; i++) {
        int s, c;
        cin >> s >> c;
        if(a[s] == -1 || a[s] == c) {
            a[s] = c;
        } else {
            ok = false;
        }
    }
    if(!ok || a[1] == 0 && n != 1) {
        cout << -1 << "\n";
        return ;
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] == -1) {
            if(i == 1 && i != n) {
                a[i] = 1;
            } else {
                a[i] = 0;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i];
    }
    cout << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
