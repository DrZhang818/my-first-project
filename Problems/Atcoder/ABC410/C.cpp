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
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    int pos = 0;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            a[(pos + p) % n] = x;
        } else if(op == 2) {
            int p;
            cin >> p;
            p--;
            cout << a[(pos + p) % n] << "\n";
        } else {
            int k;
            cin >> k;
            pos = (pos + k) % n;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
