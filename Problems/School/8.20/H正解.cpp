#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://atcoder.jp/contests/abc258/tasks/abc258_h
/*
    DP || 矩阵
    题意:
        给定一个长度为N的数组a和一个整数S
        定义一个序列是合法的, 当且仅当序列满足以下条件:
        (1)序列中每一项都是正奇数 
        (2)序列的所有项之和为S
        (3)序列的每个前缀和都不能与a中的任何一个元素相等
        求合法序列数量, 结果对998244353取模
        范围: N∈[1,1e5], 1 <= a[1] < a[2] <...< a[N] < S <= 1e18
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        对于这种多条件问题, 我们可以先忽略一部分条件, 考虑题目的easy版本:
        我们忽略条件(3), 思考在满足(1)(2)的情况下如何进行计数?
        由于每项都是正数, 因此前缀和序列是递增的, 这启发我们可以进行dp
        
    
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

using Matrix = array<array<int,2>,2>;
using Vector = array<int,2>;

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c{};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                add(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return c;
}

Vector operator * (const Matrix &a, const Vector &b) {
    Vector c{};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            add(c[i], 1LL * a[i][j] * b[j] % MOD);
        }
    }
    return c;
}

Matrix mat{1, 1, 1, 0};

Matrix fast_pow(Matrix a, ll b) {
    Matrix res{1, 0, 0, 1};
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    ll S;
    cin >> n >> S;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a.push_back(S);
    Vector f{1, 0};
    for(int i = 0; i <= n; i++) {
        ll L = a[i], R = a[i + 1];
        Matrix to = fast_pow(mat, R - L - 1);
        f = to * f;
        if(i != n) {
            swap(f[0], f[1]);
        }
    }
    cout << f[0] << "\n";
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
