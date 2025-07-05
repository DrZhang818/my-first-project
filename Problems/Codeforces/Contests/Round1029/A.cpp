#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, x;
    cin >> n >> x;
    int l = -1, r = -1;
    for(int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        if(t) {
            if(l == -1) l = i;
            r = i;
        }
    }
    if(r - l + 1 <= x) {
        cout << "YES\n"; 
    } else {
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
