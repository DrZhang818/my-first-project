#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    array<int, 11> a{};
    for(int i = 1; i <= 9; i++) {
        cin >> a[i];
    }

    int t = min(a[2], a[1]);
    a[2] -= t;
    a[3] += t;
    a[1] -= t;

    t = a[1] / 3;
    a[3] += t;
    a[1] %= 3;

    if(a[1] == 2) {
        a[2] += 1;
        a[1] = 0;
    } else if(a[1] == 1) {
        for(int i = 2; i <= 9; i++) {
            if(a[i]) {
                a[i + 1]++;
                a[1]--;
                a[i]--;
                break;
            }
        }
    }

    int ans = 1;
    for(int i = 2; i <= 10; i++) {
        ans = 1LL * ans * power(i, a[i]) % MOD;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

/*
7
5 3 0 0 0 0 0 0 0
4 1 1 1 0 0 0 0 0
1 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 2
99 88 77 66 55 44 33 22 11
100 90 80 70 60 50 40 30 20
*/
