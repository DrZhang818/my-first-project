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
    int l = 1, r = n;
    while(l < n && a[l + 1] == a[l]) {
        l++;
    }
    while(r > 1 && a[r - 1] == a[r]) {
        r--;
    }
    if(l + 1 > r - 1) {
        cout << "YES\n";
        return;
    }
    int x = a[l + 1];
    for(int i = l + 1; i <= r - 1; i++) {
        if(a[i] != x) {
            cout << "NO\n";
            return;
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
