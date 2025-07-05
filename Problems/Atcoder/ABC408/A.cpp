#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, s;
    cin >> n >> s;
    bool ok = true;
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x - cur > s) {
            cout << "No\n";
            return ;
        } else {
            cur = x;
        }
    }
    cout << "Yes\n";
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
