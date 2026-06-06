#include <iostream>
#include <cstdio>

using namespace std;

bool solve(long long d, long long b) {
    if(d < 0) return false;
    if(!b) return d == 0;
    d -= b;
    if(d < b / 2) return solve(d, b / 4);
    return solve(d, b / 2);
}

long long t, a, b, c;

int main() {
    scanf("%lld", &t);
    while(t--) {
        scanf("%lld%lld%lld", &a, &b, &c);
        printf(solve(c - a, b) ? "YES\n" : "NO\n");
    }
    return 0;
}
