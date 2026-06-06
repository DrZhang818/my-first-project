#include <iostream>
#include <cstdio>
#include <vector>

#define MOD 998244353LL

using namespace std;

long long n, q;
long long a[60], s[60];

long long getsum(long long r) {
    long long res = 0, d = 1;
    long long h[60] = {};
    h[n - 1] = 1;
    for(long long i = n - 1;i > 0;i--) {
        if((r >> i) & 1) {
            d = d * a[i] % MOD;
        }
        h[i - 1] = d;
    }
    res = (r & 1) ? d * a[0] % MOD : d;
    for(long long i = 0;i < n;i++) {
        if((r >> i) & 1) {
            if(i) {
                (res += h[i] * s[i - 1] % MOD) %= MOD;
            } else (res += h[0]) %= MOD;
        }
    }
    return res % MOD;
}

int main() {
    scanf("%lld", &n);
    for(long long i = 0;i < n;i++) {
        scanf("%lld", &a[i]);
        s[i] = i == 0 ? (1 + a[i]) : (s[i - 1] * (1 + a[i]) % MOD);
    }
    scanf("%lld", &q);
    for(long long i = 1, l, r;i <= q;i++) {
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", ((getsum(r) - getsum(l - 1)) % MOD + MOD) % MOD);
    }
    return 0;
}
