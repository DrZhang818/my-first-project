#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 50000;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int S[N + 1][201];
int C[201][101];
void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    cout << 1LL * S[n - 1][a + b - 2] * C[a + b - 2][a - 1] % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    S[0][0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= 200; j++) {
            S[i][j] = S[i - 1][j - 1];
            add(S[i][j], 1LL * (i - 1) * S[i - 1][j] % MOD);
        }
    }
    for(int i = 0; i <= 200; i++) {
        for(int j = 0; j <= i && j <= 100; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = ((ll)C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
