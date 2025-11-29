#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll query(int op, int l, int r) {
    cout << op << " " << l << " " << r << endl;
    ll x;
    cin >> x;
    return x;
}

void solve() {
    int n;
    cin >> n;
    ll sum = 1LL * (n + 1) * n / 2;
    ll sum2 = query(2, 1, n);
    int len = sum2 - sum;
    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        ll q1 = query(1, 1, mid);
        ll q2 = query(2, 1, mid);
        if(q1 != q2) {
            r = mid;
        } else {
            l = mid;
        }
    } 
    cout << "! " << r << " " << r + len - 1 << endl;
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
