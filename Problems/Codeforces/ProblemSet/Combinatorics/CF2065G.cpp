#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int N = 200000;

vector<int> minp, primes;

int init = []() {
    minp.resize(N + 1);

    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }

    return 0;
}();

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> cnt(n + 1);

    ll ans = 0;

    ll cur = 0;
    for(auto x : a) {
        if(minp[x] == x) { 
            ans += cur - cnt[x];
            cur++;
            cnt[x]++;
        }
    }

    for(auto x : a) {
        int y = x / minp[x];
        if(minp[y] == y) {
            cnt[x]++;
            ans += cnt[minp[x]] + cnt[x];
            if(y != minp[x]) {
                ans += cnt[y];
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
