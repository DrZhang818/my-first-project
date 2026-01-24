#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 100000;

vector<int> minp, primes;
int sieve = []() {
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
    return 1;
}();

void solve() {  
    int n;
    cin >> n;
    vector<int> cnt(N + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while(minp[x] > 1) {
            int p = minp[x];
            cnt[p]++;
            while(minp[x] == p) {
                x /= p;
            }
        }
    }
    int ans = *max_element(cnt.begin() + 1, cnt.end());
    cout << max(1, ans) << "\n";
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
