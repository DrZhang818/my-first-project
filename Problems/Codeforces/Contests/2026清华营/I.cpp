#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long long q, B;
char opt[10];
long long rs[10001];
long long bc[10001];
long long c[200001];

int main() {
    scanf("%lld", &q);
    B = 600;
    for(long long i = 1, x, k, t;i <= q;i++) {
        scanf("%s", opt);
        if(opt[0] == '+') {
            scanf("%lld%lld", &x, &k);
            if(k <= B) {
                rs[k] += x;
            } else {
                for(long long i = 1;i <= 200000;i += k * 2) {
                    bc[i / B] += x;
                    c[i] += x;
                    if(i + k <= 200000) {
                        bc[(i + k) / B] -= x;
                        c[i + k] -= x;
                    }
                }
            }
        }
        if(opt[0] == '-') {
            scanf("%lld%lld", &x, &k);
            if(k <= B) {
                rs[k] -= x;
            } else {
                for(long long i = 1;i <= 200000;i += k * 2) {
                    bc[i / B] -= x;
                    c[i] -= x;
                    if(i + k <= 200000) {
                        bc[(i + k) / B] += x;
                        c[i + k] += x;
                    }
                }
            }
        }
        if(opt[0] == '?') {
            scanf("%lld", &t);
            long long ans = 0;
            for(long long i = 1;i <= B;i++) {
                if((t - 1) % (i * 2) < i) {
                    ans += rs[i];
                }
            }
            for(long long i = 0;(i + 1) * B - 1 < t;i++) {
                ans += bc[i];
            }
            for(long long i = t / B * B;i <= t;i++) {
                ans += c[i];
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
