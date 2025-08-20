#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll mod(ll a, ll p) {
    return (a % p + p) % p;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
int A, B, C, st, cnt = 0;
void solve() {
    ll M = 23 * 28 * 33;
    A = mod(A - st, 23);
    B = mod(B - st, 28);
    C = mod(C - st, 33);
    ll x = 0;
    x += A * M / 23 * inv(M / 23, 23);
    x += B * M / 28 * inv(M / 28, 28);
    x += C * M / 33 * inv(M / 33, 33);
    x %= M;
    if(x == 0) {
        x = 23 * 28 * 33;
    }
    cout << "Case " << cnt << ": the next triple peak occurs in " << x << " days." << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        while(cin >> A >> B >> C >> st) {
            if(A == -1) break;
            cnt++;
            solve();
        }
    }
    return 0;
}
