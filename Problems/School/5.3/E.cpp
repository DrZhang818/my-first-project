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
    vector<int> a(n + 1), b(n + 1, -1), c(n + 1, -1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n - 1; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n - 2; i++) {
        cin >> c[i];
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.begin() + n);
    sort(c.begin() + 1, c.begin() + n - 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] != b[i]) {
            cout << a[i] << "\n";
            break;
        }
    }
    for(int i = 1; i <= n - 1; i++) {
        if(b[i] != c[i]) {
            cout << b[i] << "\n";
            break;
        }
    }
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
