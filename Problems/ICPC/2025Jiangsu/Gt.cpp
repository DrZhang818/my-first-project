#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


int solve(vector<int> &a, int m) {
    int n = a.size() - 1;
    map<PII,int> mp;
    auto f = [&](this auto &&f, int x, int y) -> int {
        if(mp.contains({x, y})) return mp[{x, y}];
        if(y == 1) return x;
        return mp[{x, y}] = x / a[y] + f(x % a[y], y - 1);
    };
    int cnt = 0;
    for(int x = 1; x <= 100000; x++) {
        if(f(x, n) == m) {
            cnt++;
        }
    }
    return cnt;
}

ll dp[1000005], b[1000005], pref[1000005];
int solve2(vector<int> &a, int m) {
    ll n, q, maxx=0; 
    ll qwq;
    n = a.size() - 1;
    pref[0] = b[0] = 1;
    for (int i=1; i<a[n]; i++) {
        qwq = a[upper_bound(a.begin() + 1, a.end(), i)-a.begin() - 1]; 
        dp[i] = dp[i-qwq] + 1; 
        b[dp[i]]++; 
        maxx = max(maxx, dp[i]);
    } 
    for (int i=1; i<=maxx; i++) pref[i] = pref[i-1] + b[i]; 
    return pref[min((ll)m, maxx)];
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n = 2;
    vector<int> a(n + 1);
    for(int t = 1; t <= 100; t++) {
        a[1] = 1;
        for(int i = 2; i <= n; i++) {
            a[i] = get(a[i - 1] + 1, 10);
        }
        cerr << t << "\n\n";
        for(int m = 1; m <= 20; m++) {
            ll ans1 = solve(a, m);
            ll ans2 = solve2(a, m);
            if(ans1 != ans2) {
                for(int i = 1; i <= n; i++) {
                    cerr << a[i] << " \n"[i == n];
                }
                cerr << m << "\n";
                cerr << ans1 << " " << ans2 << "\n";
            }
            cerr << "\n";
        }
    }
    return 0;
}
