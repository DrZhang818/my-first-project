#include <iostream>
#include <cstdio>

#define MOD 1000000007LL

using namespace std;

long long gray(string *s, int len, bool rev) {
    if(len == 1) return ((*s)[0] - '0');
    long long l = gray(s, len >> 1, !rev);
    long long r = gray(s + (len >> 1), len >> 1, rev);
    return rev ? (l * (len >> 1) % MOD + r) % MOD : (r * (len >> 1) % MOD + l) % MOD;
}

int getTimes(string s) {
    int cnt = 0;
    for(int i = s.size() - 1;~i;i--) {
        if(s[i] == '1') break;
        ++cnt;
    }
    return cnt;
}

int T, k;
string s, t, r, r0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    int l;
    while(T--) {
        cin >> s >> t >> k;
        if(k > 20) {
            printf("-1\n");
            continue;
        }
        r = r0 = "";
        l = t.size();
        while(true) {
            if(l - (l & (-l)) == 0) break;
            ++l;
            r += l - t.size() == (1 << (k - 1)) ? '1' : '0';
            r0 += '0';
        }
        for(int i = 0;i < t.size();i++) {
            r += l - t.size() + i == (1 << (k - 1)) ? '1' : (s[i] == t[i] ? '1' : '0');
            r0 += s[i] == t[i] ? '1' : '0';
        }
        if(getTimes(r0) < (1 << (k - 1))) {
            // printf("-1\n");
            // continue;
        }
        printf("%lld\n", gray(&r, l, false));
    }
    return 0;
}
