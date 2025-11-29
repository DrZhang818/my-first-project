#include <bits/stdc++.h>
using namespace std;
int fast_pow(int a, int b, int MOD) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res = 1LL * res * a % MOD;
        }
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int B[] = {2, 7, 61};
bool MR(int n) {
    if(n <= 1) return false;
    for(int p : B) {
        if(n == p) return true;
        if(n % p == 0) return false;
    }
    int m = n - 1 >> __builtin_ctz(n - 1);
    for(int p : B) {
        cerr << "p: " << p << "\n";
        int t = m, a = fast_pow(p, m, n);
        cerr << "! " << a << "\n";
        while(t != n - 1 && a != 1 && a != n - 1) {
            cerr << "a: " << a << " t: " << t << '\n';
            a = 1LL * a * a % n;
            cerr << ":: " << a << "\n";
            t <<= 1;
        }
        if(a != n - 1 && t % 2 == 0) return false;
    }
    return true;
}

int main() {

    int n = 1463;
    if(MR(n)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}