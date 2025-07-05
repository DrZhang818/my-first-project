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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int c1 = a[1] == 1;
    for(int i = 2; i <= n; i++) {
        c1 += a[i] == 1;
        if(a[i] == 0 && a[i - 1] == 0) {
            cout << "YES\n";
            return;
        }
    }
    if(c1 == n) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
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
