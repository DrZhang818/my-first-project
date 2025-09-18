#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr db EPS = 1e-7;
void gauss(vector<vector<db>> &a) {
    int n = a.size() - 1;
    for(int cur = 1; cur <= n; cur++) {
        int mx = cur;
        for(int i = 1; i <= n; i++) {
            if(i < cur && abs(a[i][cur]) >= EPS) continue;
            if(abs(a[i][cur]) > a[mx][cur]) mx = i;
        }
        swap(a[mx], a[cur]);
        if(abs(a[cur][cur]) < EPS) continue;
        db temp = a[cur][cur];
        for(int j = cur; j <= n + 1; j++) a[cur][j] /= temp;
        for(int i = 1; i <= n; i++) {
            if(i == cur) continue;
            db fac = a[i][cur];
            for(int j = cur; j <= n + 1; j++) a[i][j] -= a[cur][j] * fac;
        }
    }
}

//模运算加法

const int MOD = 998244353;
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void gauss(vector<vector<int>> &a) {
    int n = a.size() - 1;
    for(int cur = 1; cur <= n; cur++) {
        int mx = cur;
        for(int i = 1; i <= n; i++) {
            if(i < cur && a[i][cur] > 0) continue;
            if(a[i][cur] > a[mx][cur]) mx = i;
        }
        swap(a[mx], a[cur]);
        if(a[cur][cur] == 0) continue;
        int tmp = inv(a[cur][cur]);
        for(int j = cur; j <= n + 1; j++) a[cur][j] = 1LL * a[cur][j] * tmp % MOD;
        for(int i = 1; i <= n; i++) {
            if(i == cur) continue;
            int fac = a[i][cur];
            for(int j = cur; j <= n + 1; j++) a[i][j] = (a[i][j] - 1LL * a[cur][j] * fac % MOD + MOD) % MOD;
        }
    }
}