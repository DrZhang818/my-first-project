#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//1.杨辉三角法 O(n^2) 支持n <= 62
void solve1() {
    const int n = 62;
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
}
//2.组合数定义法 O(n^2) C[i][j] = i!/(j! * (i-j)!) = C[i][j-1] * (i-j+1) / j
void solve2() {
    const int n = 62;
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            C[i][j] = C[i][j - 1] * (i - j + 1) / j;
        }
    }
}
//3.计算单行组合数 O(n) 原理同2
void solve3() {
    int n;
    cin >> n;
    vector<ll> C(n + 1, 1);
    for(int j = 1; j <= n; j++) {
        C[j] = C[j - 1] * (n - j + 1) / j;
    }
}
//4.预处理阶乘+逆元 计算带模组合数 O(nlogn)
ll pow_mod(ll a, ll b, int MOD) {
    ll res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve4() {
    const int MOD = 1000000007;
    vector<ll> fac(10001);
    vector<ll> inv(10001);
    fac[0] = 1;
    for(int i = 1; i <= 10000; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = pow_mod(fac[i], MOD - 2, MOD);
    }
    auto C = [&](int n, int m) -> int {
        return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
    };
    int n, m;
    cin >> n >> m;
    cout << C(n, m) << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve4();
    return 0;
}