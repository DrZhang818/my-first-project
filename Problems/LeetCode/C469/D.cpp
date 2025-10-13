#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

using Matrix = vector<vector<int>>;

Matrix operator * (const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            if(a[i][k] == 0) continue;
            for(int j = 0; j < n; j++) {
                add(res[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return res;
}

Matrix fast_pow(Matrix a, int b) {
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int k = r - l + 1;
        Matrix a(k, vector<int>(k));
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < k - i - 1; j++) {
                a[i][j] = 1;
            }
        }
        a = fast_pow(a, n - 1);
        int ans = 0;
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < k; j++) {
                add(ans, a[i][j]);
            }
        }
        return 2LL * ans % MOD;
    }
};