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
    101
    球相同  盒子不同  可以为空
    方法数为:
        C(n + m - 1, m - 1)
    C为组合数
*/
ll C[N + 1][N + 1];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    int n, m;
    cin >> n >> m;
    cout << C[n + m - 1][m - 1] << "\n";
    return 0;
}
