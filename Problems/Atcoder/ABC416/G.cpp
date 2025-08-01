#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> ss(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> ss[i];
    }
    sort(ss.begin() + 1, ss.end(), [&](auto s, auto t){
        return s + t < t + s;     
    });
    vector<string> a(11);
    for(int i = 1; i <= n; i++) {
        int sz = ss[i].size();
        if(a[sz].empty()) {
            a[sz] = ss[i];
        }
    }
    string T;
    while(T.size() < 20) T += ss[1];
    int len = ss[1].size();
    vector<int> dp(len, 0);
    for(int i = 0; i < k; i++) {
        vector<int> ndp(len, inf);
        for(int j = 0; j < len; j++) {
            if(dp[j] == inf) continue;
            for(int sz = 1; sz <= 10; sz++) {
                if(a[sz].empty()) continue;
                int st = ((j - sz) % len + len) % len;
                if(T.substr(st, sz) == a[sz]) {
                    ndp[st] = min(ndp[st], sz + dp[j]);
                }
            }
        }
        swap(dp, ndp);
    }
    for(int i = 0; i < dp[0]; i++) {
        cout << T[i % len];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
