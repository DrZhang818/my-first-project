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
    int d = a[2] - a[1];
    if(a[1] - d < 0 || a[n] + d < 0) {
        cout << "NO\n";
        return;
    }
    if(d >= 0 && (a[1] - d) % (n + 1) != 0 || d < 0 && (a[n] + d) % (n + 1) != 0) {
        cout << "NO\n";
        return;
    }
    for(int i = 2; i <= n; i++) {
        if(a[i] - a[i - 1] != d) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
