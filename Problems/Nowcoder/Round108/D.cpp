#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
const int N = 200000;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int mi[N + 1];
void solve() {
    int n;
    cin >> n;
    int odd = 0, even = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x & 1) {
            odd += 1;
        } else {
            even += 1;
        }
    }
    cout << 1LL * (mi[even] - 1) * mi[odd] % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mi[0] = 1;
    for(int i = 1; i <= N; i++) {
        mi[i] = 2LL * mi[i - 1] % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
