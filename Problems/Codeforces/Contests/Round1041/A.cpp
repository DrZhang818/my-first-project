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
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == 0) ok = false;
    }
    if(!ok) {
        cout << "NO\n";
        return;
    }
    if(a[2] == -1) a[2] = a[1];
    for(int i = 2; i <= n - 1; i++) {
        if(a[i - 1] == -1 && a[i] == -1 && a[i + 1] == -1) continue;
        if(a[i] == -1) {
            if(a[i - 1] == -1) {
                a[i] = a[i - 1] = a[i + 1];
            } else if(a[i + 1] == -1) {
                a[i] = a[i + 1] = a[i - 1];
            } else if(a[i - 1] != a[i + 1]) {
                cout << "NO\n";
                return;
            } else {
                a[i] = a[i + 1];
            }
        } else {
            if(a[i - 1] == -1) a[i - 1] = a[i];
            if(a[i + 1] == -1) a[i + 1] = a[i];
            if(a[i - 1] != a[i] || a[i + 1] != a[i]) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
