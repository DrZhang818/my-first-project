#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    a[1] = 1, a[2] = 2;
    for(int i = 3; i <= n; i++) {
        a[i] = a[i - 1] + a[i - 2];
    }
    auto cal = [&](int w, int l, int h) -> bool {
        int mn = a[n], mx = a[n] + a[n - 1];
        if(w < mn || l < mn || h < mn) return false;
        if(w < mx && l < mx && h < mx) return false;
        return true;
    };
    while(q--) {
        int w, l, h;
        cin >> w >> l >> h;
        if(cal(w, l, h)) {
            cout << "1";
        } else {
            cout << "0";
        }
    }
    cout << "\n";
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
