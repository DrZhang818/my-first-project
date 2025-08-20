#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 500000;

void solve() {
    vector<int> a(N + 1);
    int B = sqrt(N / 4);
    vector sum(B, vector<ll>(B)); 
    int q;
    cin >> q;
    while(q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1) {
            a[x] += y;
            for(int i = 1; i < B; i++) {
                sum[i][x % i] += y;
            }
        } else {
            if(x < B) {
                cout << sum[x][y] << "\n";
            } else {
                ll res = 0;
                for(int i = y; i <= N; i += x) {
                    res += a[i];
                }
                cout << res << "\n";
            }
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
