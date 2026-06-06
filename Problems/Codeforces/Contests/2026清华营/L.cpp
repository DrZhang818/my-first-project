#include <iostream>
#include <cstdio>

using namespace std;

long long n, q;
long long s[200001];
long long s2[200001];

int main() {
    scanf("%lld%lld", &n, &q);
    for(long long i = 1, x;i <= n;i++) {
        scanf("%lld", &x);
        s[i] = s[i - 1] + x;
        s2[i] = s2[i - 1] + x * x;
    }
    for(long long i = 1, l, r, S;i <= q;i++) {
        scanf("%lld%lld%lld", &l, &r, &S);
        long long sum = s[r] - s[l - 1];
        if(sum > S) {
            printf("-1\n");
            continue;
        }
        long long ans = sum * (S - sum) + (sum * sum - (s2[r] - s2[l - 1])) / 2;
        printf("%lld\n", ans);
    }
    return 0;
}
