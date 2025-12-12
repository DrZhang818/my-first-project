#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    int tar = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        tar += a[i];
    }
    if(tar % n != 0) {
        cout << -1 << "\n";
        return;
    }
    tar /= n;
    vector<int> sum(1 << n);
    for(int i = 0; i < n; i++) {
        sum[1 << i] = a[i] - tar;
    }
    for(int i = 0; i < n; i++) {
        for(int s = 0; s < 1 << n; s++) {
            if(~s >> i & 1) s |= 1 << i;
            sum[s] += sum[s ^ (1 << i)];
        }
    }
    vector<int> dp(1 << n, inf), nxt(1 << n);
    dp[0] = 0;
    for(int s = 1; s < 1 << n; s++) {
        int add = sum[s] == 0 ? 0 : 1;
        for(int i = 0; i < n; i++) {
            if(s >> i & 1) {
                int res = dp[s ^ (1 << i)] + add;
                if(res < dp[s]) {
                    dp[s] = res;
                    nxt[s] = i;
                }    
            }
        }
    }
    int s = (1 << n) - 1;
    cout << dp[s] << "\n";
    while(s) {
        ll S = 0;
        vector<int> p;
        do {
            int i = nxt[s];
            int sub = 1 << i;
            p.push_back(i);
            S += sum[sub];
            s ^= sub;
        } while (S);
        sort(p.begin(), p.end(), 
            [&](auto x, auto y) {
                return a[x] > a[y];
            });
        for(int i = 0; i < int(p.size()) - 1; i++) {
            cout << p[i] + 1 << " " << p[i + 1] + 1 << " " << a[p[i]] - tar << "\n";
            a[p[i + 1]] += a[p[i]] - tar;
        }
    }
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
