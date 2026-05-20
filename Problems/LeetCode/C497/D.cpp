#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 5E4;
constexpr int MOD = 998244353;

vector<int> minp, primes, mu;
vector<int> divs[N + 1];
int pow2[N + 1];
auto init = [] {
    minp.resize(N + 1);
    mu.resize(N + 1);
    mu[1] = 1;
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            mu[i] = MOD - 1;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                mu[i * p] = 0;
            } else {
                mu[i * p] = 1LL * mu[i] * mu[p] % MOD; 
            }
        }
    }

    pow2[0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            divs[j].push_back(i);
        }
        pow2[i] = pow2[i - 1] * 2LL % MOD;        
    }

    return 1;
}();

int cnt[N + 1];
int T[N + 1];
int timer = 0;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

class Solution {
public:
    int countGoodSubseq(vector<int>& a, int p, vector<vector<int>>& Q) {
        timer++;

        int n = a.size();
        for(int i = 0; i < n; i++) {
            if(a[i] % p != 0) continue;
            for(int d : divs[a[i]]) {
                if(T[d] != timer) {
                    T[d] = timer;
                    cnt[d] = 0;
                }
                cnt[d]++;
            }
        }

        auto g = [&](int d) {
            return ((pow2[cnt[d]] - 1 - (cnt[d] == n)) % MOD + MOD) % MOD;
        };

        int ans = 0, res = 0;
        for(int i = 1; i * p <= N; i++) {
            if(T[i * p] != timer) continue;
            add(ans, 1LL * mu[i] * g(i * p) % MOD);
        }        

        for(auto& vec : Q) {
            int idx = vec[0], val = vec[1];
            if(a[idx] % p == 0) {
                for(int d : divs[a[idx]]) {
                    if(d % p == 0) {
                        add(ans, MOD - 1LL * mu[d / p] * g(d) % MOD);
                    }
                    cnt[d]--;
                    if(d % p == 0) {
                        add(ans, 1LL * mu[d / p] * g(d) % MOD);
                    }
                }
            }
            if(val % p == 0) {
                for(int d : divs[val]) {
                    if(T[d] != timer) {
                        T[d] = timer;
                        cnt[d] = 0;
                    }
                    if(d % p == 0) {
                        add(ans, MOD - 1LL * mu[d / p] * g(d) % MOD);
                    }
                    cnt[d]++;
                    if(d % p == 0) {
                        add(ans, 1LL * mu[d / p] * g(d) % MOD);
                    }
                }
            }
            a[idx] = val;
            if(ans != 0) {
                res++;
            }
        }

        return res;
    }
};