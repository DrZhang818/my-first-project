#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

i64 power(i64 a, i64 b, i64 m) {
    i64 res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return res;
}

void solve() {
    int K, M;
    cin >> K >> M;

    i64 P = 1LL * 10007 * 9 * M;

    i64 N = 0;

    for(int i = 1; i <= K; i++) {
        int c, l;
        cin >> c >> l;
        
        i64 t = power(10, l, P);
        N = (1LL * N * t + 1LL * c * (t - 1 + P) % P) % P;
    }

    cout << N / 9 / M << "\n";
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
