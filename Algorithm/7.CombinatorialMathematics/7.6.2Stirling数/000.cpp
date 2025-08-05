#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 10;

//https://www.luogu.com.cn/problem/P1287
/*
    000
    球不同  盒子不同  要求非空
    方法数为:
        m! * S(n,m)
    S(n,m)为第二类Stirling数

*/
int S[N + 1][N + 1];
void solve() {
    int n, k;
    cin >> n >> k;
    cout << S[n][k] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    S[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int k = 1; k <= n; k++) {
            S[n][k] = k * S[n - 1][k - 1] + k * S[n - 1][k];
        }
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
