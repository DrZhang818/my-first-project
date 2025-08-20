#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e15;
const int MOD = 1000000007;

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
class Solution {
public:
    int xorAfterQueries(vector<int>& a, vector<vector<int>>& Q) {
        int n = a.size();
        int B = sqrt(Q.size());
        vector<vector<int>> D(B);
        for(auto &q : Q) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            if(k < B) {
                if(D[k].empty()) {
                    D[k].resize(n + k, 1);
                }
                D[k][l] = 1LL * D[k][l] * v % MOD;
                r = r - (r - l) % k + k;
                D[k][r] = 1LL * D[k][r] * inv(v) % MOD;
            } else {
                for(int i = l; i <= r; i += k) {
                    a[i] = 1LL * a[i] * v % MOD;
                }
            }
        }
        for(int k = 1; k < B; k++) {
            auto &d = D[k];
            if(d.empty()) continue;
            for(int i = 0; i < k; i++) {
                int pre = 1;
                for(int j = i; j < n; j += k) {
                    pre = 1LL * pre * d[j] % MOD;
                    a[j] = 1LL * a[j] * pre % MOD;
                }
            }
        }
        return reduce(a.begin(), a.end(), 0, bit_xor());
    }
};