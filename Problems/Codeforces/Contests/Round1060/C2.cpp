#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = int(1E6);

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
        for(int p : adj_pr[a[i]]) {
            mp[p]++;
        }
    }
    for(auto &[p, c] : mp) {
        if(c >= 2) {
            cout << 0 << "\n";
            return;
        }
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), 
        [&](auto x, auto y) {
            return b[x] < b[y];
        });

    int ans = INT_MAX;
    int mn = b[p[1]] + b[p[2]];   
    int R = 1;
    while(R + 1 <= n && b[p[R + 1]] <= mn) {
        R++;
    }
    for(int s = 1; s <= R; s++) {
        int i = p[s];
        int x = a[i] + 1;
        bool ok = false;
        for(int pr : adj_pr[x]) {
            if(mp.contains(pr)) {
                ans = min(ans, b[i]);
                ok = true;
                break;
            }
        }
        if(ok) {
            break;
        }
    }
    ans = min(ans, mn);
    int x = a[p[1]];
    for(int pr : adj_pr[x]) {
        mp[pr]--;
        if(mp[pr] == 0) {
            mp.erase(pr);
        }
    }
    if(mp.empty()) {
        cout << ans << "\n";
        return;
    }
    x = a[p[1]];
    for(auto [pr, _] : mp) {
        int t = (pr - (x % pr)) % pr;
        if(1LL * b[p[1]] * t >= ans) {
            continue;
        }
        ans = min(ans, b[p[1]] * t);
    }
    cout << ans << "\n";
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
