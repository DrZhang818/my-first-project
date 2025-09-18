#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
const int N = 1000000;

int fac[N + 1];

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    vector<int> cnt(N + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    sort(a.begin() + 1, a.end());
    ll sum = 0, pre = 0;
    for(int i = 1; i <= n; i++) {
        pre += a[i];
        sum += i * a[i] - pre;
    }
    cout << sum << " ";
    ll c;
    if(sum == 0) {
        c = 1;
    } else {
        c = 2;
    }
    for(int i = 1; i <= N; i++) {
        c = c * fac[cnt[i]] % MOD;
    }
    cout << c << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * i * fac[i - 1] % MOD;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
