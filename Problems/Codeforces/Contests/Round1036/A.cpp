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
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    if(n == 1) {
        cout << "NO\n";
        return;
    }
    for(int i = n - 1; i >= 1; i--) {
        b[i] = min(b[i], b[i + 1]);
    }
    for(int i = 1; i < n; i++) {
        int x = a[i];
        if(b[i + 1] < a[i]) {
            cout << "YES\n";
            cout << 2 << "\n";
            cout << a[i] << " " << b[i + 1] << "\n";
            return;
        }
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
