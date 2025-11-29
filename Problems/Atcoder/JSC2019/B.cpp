#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> cnt(2001);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int x = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(a[i] > a[j]) {
                x++;
            }
        }
    }
    int b = 0;
    for(int i = 1; i <= 2000; i++) {
        for(int j = 1; j < i; j++) {
            add(b, 1LL * cnt[i] * cnt[j] % MOD);
        }
    }
    int ans = 1LL * k * x % MOD;
    add(ans, 1LL * k * (k - 1) / 2 % MOD * b % MOD);
    cout << ans << "\n";
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
