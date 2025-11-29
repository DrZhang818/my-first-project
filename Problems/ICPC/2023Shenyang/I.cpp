#include <iostream>
#include <cstdio>

#define MOD 1000000007LL

using namespace std;

long long t, p[4][2];
bool f[4][2];
int s[2];

long long solve2() {
    if(s[0] == 0 || s[1] == 0) return 0;
    int tmp = 0;
    long long h = 0, w = 0;
    for(int i = 1;i <= 3;i++) {
        if(!f[i][0] && !f[i][1]) {
            tmp = i;
        }
    }
    if(tmp == 0) {
        int tmph = 0, tmpw = 0;
        for(int i = 1;i <= 3;i++) {
            if(f[i][0]) tmph = i;
            if(f[i][1]) tmpw = i;
        }
        tmp = 6 - tmph - tmpw;
    }
    for(int i = 1;i <= 3;i++) {
        if(i != tmp) {
            if(!f[i][0]) h = p[i][0];
            if(!f[i][1]) w = p[i][1];
        }
    }
    return (h + p[tmp][0] >= p[0][0] && w + p[tmp][1] >= p[0][1]) ? 4 : 0;
}

long long solve1(int x) {
    if(s[x] == 3) {
        if(p[1][x ^ 1] + p[2][x ^ 1] + p[3][x ^ 1] < p[0][x ^ 1]) return 0;
        long long s = 0;
        if(p[1][x ^ 1] + p[2][x ^ 1] >= p[0][x ^ 1]) {
            s += max(0LL, p[0][x ^ 1] - p[3][x ^ 1] - 1);
        } else {
            s += max(0LL, min(p[1][x ^ 1] + 1, p[0][x ^ 1] - p[3][x ^ 1]) - max(p[0][x ^ 1] + 1 - p[2][x ^ 1] - p[3][x ^ 1], 2LL) + 1);
        }
        if(p[2][x ^ 1] + p[3][x ^ 1] >= p[0][x ^ 1]) {
            s += max(0LL, p[0][x ^ 1] - p[1][x ^ 1] - 1);
        } else {
            s += max(0LL, min(p[2][x ^ 1] + 1, p[0][x ^ 1] - p[1][x ^ 1]) - max(p[0][x ^ 1] + 1 - p[3][x ^ 1] - p[1][x ^ 1], 2LL) + 1);
        }
        if(p[3][x ^ 1] + p[1][x ^ 1] >= p[0][x ^ 1]) {
            s += max(0LL, p[0][x ^ 1] - p[2][x ^ 1] - 1);
        } else {
            s += max(0LL, min(p[3][x ^ 1] + 1, p[0][x ^ 1] - p[2][x ^ 1]) - max(p[0][x ^ 1] + 1 - p[1][x ^ 1] - p[2][x ^ 1], 2LL) + 1);
        }
        s += (max(p[1][x ^ 1], p[2][x ^ 1]) + p[3][x ^ 1] >= p[0][x ^ 1]) ? 1 : 0;
        s += (max(p[2][x ^ 1], p[3][x ^ 1]) + p[1][x ^ 1] >= p[0][x ^ 1]) ? 1 : 0;
        s += (max(p[3][x ^ 1], p[1][x ^ 1]) + p[2][x ^ 1] >= p[0][x ^ 1]) ? 1 : 0;
        return s * 2LL % MOD;
    }
    if(s[x] == 2) {
        int tmp = 6;
        long long sum = 0;
        for(int i = 1;i <= 3;i++) {
            if(f[i][x]) {
                tmp -= i;
            }
        }
        for(int i = 1;i <= 3;i++) {
            if(tmp != i) {
                sum += p[i][x ^ 1];
            }
        }
        return (sum >= p[0][x ^ 1]) 
        ? 2LL * (p[0][0] - p[tmp][0] + 1) * (p[0][1] - p[tmp][1] + 1) : 0;
    }
    if(s[x] == 0) return 0;
    int tmp = 0;
    long long sum = 0, mn = 1e9;
    for(int i = 1;i <= 3;i++) {
        if(f[i][x]) {
            tmp = i;
        }
    }
    for(int i = 1;i <= 3;i++) {
        if(tmp != i) {
            mn = min(mn, p[i][x ^ 1]);
            sum += p[i][x];
        }
    }
    return (sum >= p[0][x] && mn + p[tmp][x ^ 1] >= p[0][x ^ 1]) ? 4 : 0;
}

long long solve() {
    for(long long i = 1;i <= 3;i++) {
        if(p[i][0] == p[0][0] && p[i][1] == p[0][1]) {
            return (p[0][0] - p[1][0] + 1) * (p[0][1] - p[1][1] + 1) % MOD
            * (p[0][0] - p[2][0] + 1) % MOD * (p[0][1] - p[2][1] + 1) % MOD
            * (p[0][0] - p[3][0] + 1) % MOD * (p[0][1] - p[3][1] + 1) % MOD;
        }
        if(p[i][0] == p[0][0]) f[i][0] = true;
        if(p[i][1] == p[0][1]) f[i][1] = true;
    }
    s[0] = s[1] = 0;
    for(int i = 1;i <= 3;i++) {
        s[0] += f[i][0] ? 1 : 0;
        s[1] += f[i][1] ? 1 : 0;
    }
    if(s[0] == 0 && s[1] == 0) return 0;
    return (solve1(0) + solve1(1) - solve2()) % MOD;
}

int main() {
    scanf("%lld", &t);
    while(t--) {
        for(long long i = 0;i <= 3;i++) {
            scanf("%lld%lld", &p[i][0], &p[i][1]);
            f[i][0] = f[i][1] = false;
        }
        printf("%lld\n", solve());
    }
    return 0;
}
