#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 10;

//https://www.luogu.com.cn/problem/P1655
/*
    011
    球不同  盒子相同  可以为空
    方法数为:
        ∑S(n,i) i∈[1,m]
    S(n,m)为第二类Stirling数
*/
ll S[N + 1][N + 1];
ll preS[N + 1][N + 1];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    S[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int k = 1; k <= n; k++) {
            S[n][k] = S[n - 1][k - 1] + k * S[n - 1][k];
        }
    }
    preS[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int k = 1; k <= n; k++) {
            preS[n][k] = preS[n][k - 1] + S[n][k];
        }
    }
    int n, m;
    cin >> n >> m;
    cout << preS[n][m] << "\n";
    return 0;
}
