#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int fast_pow(int a, int b, int m) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return res;
}

void solve() {  
    int a, m;
    string b;
    cin >> a >> m >> b;

    if(m == 1) {
        cout << 0 << "\n";
        return;
    }

    int tm = m;
    int phi = m;
    for(int i = 2; i * i <= m; i++) {
        if(m % i) continue;
        if(m % i == 0) {
            phi = phi / i * (i - 1);
            while(m % i == 0) {
                m /= i;
            }
        }
    } 
    if(m > 1) {
        phi = phi / m * (m - 1);
    }
    m = tm;

    ll e = 0;
    int tag = 0;
    for(char c : b) {
        e = 10LL * e + (c - '0');
        if(e >= phi) {
            tag = 1;
            e %= phi;
        }
    }

    cout << fast_pow(a, e + tag * phi, m) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}