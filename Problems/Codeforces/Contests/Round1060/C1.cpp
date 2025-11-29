#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = int(2E5) + 5;

vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(p == minp[i]) break;
        }
    }
}

vector<int> adj_pr[N + 1];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        for(int d : adj_pr[a[i]]) {
            mp[d]++;
        }
    }
    for(auto &[d, c] : mp) {
        if(c >= 2) {
            cout << 0 << "\n";
            return;
        }
    }
    for(int i = 1; i <= n; i++) {
        int x = a[i] + 1;
        for(int d : adj_pr[x]) {
            if(mp.contains(d)) {
                cout << 1 << "\n";
                return;
            }
        }
    }
    cout << 2 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(N);
    for(int i = 2; i <= N; i++) {
        int x = i;
        while(x > 1) {
            int pr = minp[x];
            adj_pr[i].push_back(pr);
            while(x % pr == 0) {
                x /= pr;
            }
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
