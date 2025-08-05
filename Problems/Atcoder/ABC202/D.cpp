#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc202/tasks/abc202_d
ll C[61][31];
void solve() {
    int a, b;
    ll k;
    cin >> a >> b >> k;
    int tot = a + b;
    string ans;
    for(int i = 1; i <= tot; i++) {
        ll cnt = C[a + b - 1][b];
        if(k > cnt) {
            ans += "b";
            k -= cnt;
            b--;
        } else {
            ans += "a";
            a--;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 60; i++) {
        for(int j = 0; j <= i && j <= 30; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
